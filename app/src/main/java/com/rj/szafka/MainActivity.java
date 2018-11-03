package com.rj.szafka;

import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.rj.szafka.model.Key;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    private TextView kl1, kl2, kl3, kl4;

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    final DatabaseReference key1 = database.getReference("key1");
    final DatabaseReference key2 = database.getReference("key2");
    final DatabaseReference key3 = database.getReference("key3");
    final DatabaseReference key4 = database.getReference("key4");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
//        setSupportActionBar(toolbar);
//        toolbar.setTitle("Szafka");

        kl1 = findViewById(R.id.kluczykOne);
        kl2 = findViewById(R.id.kluczykTwo);
        kl3 = findViewById(R.id.kluczykThree);
        kl4 = findViewById(R.id.kluczykFour);


        setListeners();

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Otwieram", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
                Key key = new Key();
                key.nr = 1;
                key.used = false;
                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd.MM.yyyy_HH:mm");
                key.when = simpleDateFormat.format(new Date());
                key.model = Build.MODEL;
                key1.setValue(key);
            }
        });

//        kl1.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                Snackbar.make(v, "Otwieram", Snackbar.LENGTH_LONG)
//                        .setAction("Action", null).show();
//                Key key = new Key();
//                key.nr = 1;
//                key.used = true;
//                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd.MM.yyyy_HH:mm");
//                key.when = simpleDateFormat.format(new Date());
//                key.model = Build.MODEL;
//                key1.setValue(key);
//            }
//        });
//        kl2.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                Snackbar.make(v, "Otwieram", Snackbar.LENGTH_LONG)
//                        .setAction("Action", null).show();
//                Key key = new Key();
//                key.nr = 1;
//                key.used = false;
//                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd.MM.yyyy_HH:mm");
//                key.when = simpleDateFormat.format(new Date());
//                key.model = Build.MODEL;
//                key1.setValue(key);
//            }
//        });
    }

    private void setListeners() {

        ValueEventListener valueEventListener = new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                Key key = dataSnapshot.getValue(Key.class);
                if (key!=null)
                switch (key.nr){
                    case 1:
                        if (key.used) {
                            kl1.setBackgroundColor(Color.RED);
                            kl1.setTextColor(Color.WHITE);
                        }else{
                            kl1.setBackgroundColor(Color.GREEN);
                            kl1.setTextColor(Color.BLACK);
                        }
                        break;
                    case 2:
                        if (key.used) {
                            kl2.setBackgroundColor(Color.RED);
                            kl2.setTextColor(Color.WHITE);

                        }else{
                            kl2.setBackgroundColor(Color.GREEN);
                            kl2.setTextColor(Color.BLACK);
                        }
                        break;
                    case 3:
                        if (key.used) {
                            kl3.setBackgroundColor(Color.RED);
                            kl3.setTextColor(Color.WHITE);

                        }else{
                            kl3.setBackgroundColor(Color.GREEN);
                            kl3.setTextColor(Color.BLACK);
                        }
                        break;
                    case 4:
                        if (key.used) {
                            kl4.setBackgroundColor(Color.RED);
                            kl4.setTextColor(Color.WHITE);

                        }else{
                            kl4.setBackgroundColor(Color.GREEN);
                            kl4.setTextColor(Color.BLACK);
                        }
                        break;
                }

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        };

        key1.addValueEventListener(valueEventListener);
        key2.addValueEventListener(valueEventListener);
        key3.addValueEventListener(valueEventListener);
        key4.addValueEventListener(valueEventListener);

    }

}
