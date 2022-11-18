package com.example.datapersistence

import android.app.Application

class MyApplication : Application() {
    val db by lazy { AppDatabase.getInstance(this) }


    // Loggin or stuff before the app laucnhes, it starts here
}