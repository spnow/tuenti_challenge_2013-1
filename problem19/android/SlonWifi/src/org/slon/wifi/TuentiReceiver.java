package org.slon.wifi;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.util.Log;

public class TuentiReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {

		// get the part of the image in byte[] from the extra.
		// save it to a file (tuentiX), x = 0 to 4, for parts.
		// later reconstruct the jpeg using gnu cat (easier)
		// great problem :))
		if (intent.hasExtra("SIGNAL_INFO")) {
			byte[] key = intent.getByteArrayExtra("SIGNAL_INFO");

			File path = Environment
					.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
			File file = null;

			if (!new File(path, "tuenti0.jpg").exists()) {
				file = new File(path, "tuenti0.jpg");
			} else if (!new File(path, "tuenti1.jpg").exists()) {
				file = new File(path, "tuenti1.jpg");
			} else if (!new File(path, "tuenti2.jpg").exists()) {
				file = new File(path, "tuenti2.jpg");
			} else if (!new File(path, "tuenti3.jpg").exists()) {
				file = new File(path, "tuenti3.jpg");
			} else if (!new File(path, "tuenti4.jpg").exists()) {
				file = new File(path, "tuenti4.jpg");
			}

			try {
				file.createNewFile();
				BufferedOutputStream out = new BufferedOutputStream(
						new FileOutputStream(file));
				out.write(key);
				Log.i("--", "" + key.length);
				out.flush();

			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} else {
			Log.i("shit", intent.getDataString());
		}
	}
}