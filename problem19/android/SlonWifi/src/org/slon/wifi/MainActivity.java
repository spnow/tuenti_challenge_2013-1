package org.slon.wifi;

import java.util.HashSet;
import java.util.Set;

import android.app.Activity;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
	public static Set<Integer> seen = new HashSet<Integer>();
	TextView format = null;
	EditText input = null;
	protected String key;
	protected String ssid;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		format = (TextView) findViewById(R.id.format);
		input = (EditText) findViewById(R.id.input);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	public static final String URI = "content://com.tuenti.lostchallenge.datamodel.provider.ContestProvider/contest";

	public void doEncode(View v) {
		Uri uri = Uri.parse(URI);

		try {
			Cursor c = getApplicationContext().getContentResolver().query(uri, null, "key=?", new String[]{input.getText().toString()}, null);
			c.moveToFirst();
			Log.i("res", c.getString(0));
			format.setText("Answer is: " + c.getString(0));
		} catch(Exception e) {
			format.setText("Invalid input, cheater :P");
		}
	}
}
