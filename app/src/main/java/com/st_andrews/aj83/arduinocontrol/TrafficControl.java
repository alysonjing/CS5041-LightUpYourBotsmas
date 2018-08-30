package com.st_andrews.aj83.arduinocontrol;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Toast;
import java.io.IOException;
import java.util.UUID;

public class TrafficControl extends AppCompatActivity {

    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    SeekBar simpleSeekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_traffic_control);

        simpleSeekBar=(SeekBar)findViewById(R.id.turn_Bar);
        simpleSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChangedValue = 0;

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChangedValue = progress;
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                Toast.makeText(TrafficControl.this, "Seek bar progress is :" + progressChangedValue,
                        Toast.LENGTH_SHORT).show();
            }
        });


        Intent newInt = getIntent();
        address = newInt.getStringExtra(DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device
        new ConnectBT().execute(); //Call the class to connect
    }

    public void colorClick (View view){
        int clicked = view.getId();
        switch (clicked){
            case (R.id.turn_1):
                sendMessage("turn1");
                break;
            case (R.id.turn_2):
                sendMessage("turn2");
                break;
            case (R.id.turn_3):
                sendMessage("turn3");
                break;
            case (R.id.turn_4):
                sendMessage("turn4");
                break;
            case (R.id.color_R):
                sendMessage("color1");
                break;
            case (R.id.color_G):
                sendMessage("color2");
                break;
            case (R.id.color_B):
                sendMessage("color3");
                break;
            case (R.id.color_S):
                sendMessage("colorS");
                break;
            case (R.id.pattern_1):
                sendMessage("pattern1");
                break;
            case (R.id.pattern_2):
                sendMessage("pattern2");
                break;
            case (R.id.pattern_3):
                sendMessage("pattern3");
                break;
        }
    }

    private void sendMessage(String rMsg){
        if (btSocket!=null) {
            try {
                btSocket.getOutputStream().write(rMsg.getBytes());
            } catch (IOException e) {
                Toast.makeText(getApplicationContext(), "Error: Sending Message!", Toast.LENGTH_LONG).show();
            }
        }
    }

    //helper class for handling Bluetooth Connection
    private class ConnectBT extends AsyncTask<Void, Void, Void>
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute() {
            progress = ProgressDialog.show(TrafficControl.this, "Connecting...", "Please wait!!!");
        }

        @Override
        protected Void doInBackground(Void... devices){
            try {
                if (btSocket == null || !isBtConnected) {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();//start connection
                }
            } catch (IOException e) {
                ConnectSuccess = false;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result){
            super.onPostExecute(result);

            if (!ConnectSuccess) {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            } else {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }

        // fast way to call Toast
        private void msg(String s) {
            Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
        }
    }
}

