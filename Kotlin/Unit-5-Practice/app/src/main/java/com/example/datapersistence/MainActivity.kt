package com.example.datapersistence

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.button).setOnClickListener {
            val evenDesc = findViewById<EditText>(R.id.etEvent).text.toString()
            val date = findViewById<EditText>(R.id.etDate).text.toString()

            // TODO Save this event into the database
            lifecycleScope.launch(IO)
            {
//                (application as MyApplication).db.eventDao().deleteAll()
                (application as MyApplication).db.eventDao().insert(
                    EventEntity (
                        evenDesc,
                        date
                    )
                )
            }
        }

    }
}