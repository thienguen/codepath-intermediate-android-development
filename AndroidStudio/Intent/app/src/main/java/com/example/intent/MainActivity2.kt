package com.example.intent

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast

class MainActivity2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main2)


        val fromMainActivity = intent.getStringExtra("name")

        Toast.makeText(this, fromMainActivity, Toast.LENGTH_SHORT).show()

        val but = findViewById<Button>(R.id.button)

        but.setOnClickListener {
            finish()
        }
    }
}