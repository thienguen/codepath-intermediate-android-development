package com.example.intent

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button = findViewById<Button>(R.id.buttonClick)

        // construct the intent
        // invoke it using the startActivity method
        button.setOnClickListener {
            val intent = Intent(this, MainActivity2::class.java)
            intent.putExtra("name", "Thien")
            intent.putExtra("age", 20)
            startActivity(intent) // --> forward to the next activity
        }


    }
}