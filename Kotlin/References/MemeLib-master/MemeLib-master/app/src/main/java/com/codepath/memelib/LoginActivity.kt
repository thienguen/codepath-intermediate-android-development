package com.codepath.memelib

import android.content.Intent
import android.media.MediaPlayer
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.parse.ParseObject
import com.parse.ParseUser
import org.json.JSONArray



class LoginActivity(override var mp: MediaPlayer? = null) : AppCompatActivity(), SoundClick {
//    private var mp: MediaPlayer? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        // Code snippet to test connection to parse server.
        val firstObject = ParseObject("FirstClass")
        firstObject.put("message","Hey ! First message from android. Parse is now connected")
        firstObject.saveInBackground {
            if (it != null){
                it.localizedMessage?.let { message -> Log.e("LoginActivity", message) }
            }else{
                Log.d("LoginActivity","Object saved.")
            }
        }

        // Takes the user directly to the Main Activity if already logged in
        if (ParseUser.getCurrentUser() != null){
            goToMainActivity()
        }

        // Setting up onCLickListeners for Login and Signup buttons
        findViewById<Button>(R.id.btnLogin).setOnClickListener {
            val username = findViewById<EditText>(R.id.etUsername).text.toString()
            val password = findViewById<EditText>(R .id.etPassword).text.toString()
            startSound()
            loginUser(username, password)
        }

        findViewById<Button>(R.id.btnSignup).setOnClickListener {
            val username = findViewById<EditText>(R.id.etUsername).text.toString()
            val password = findViewById<EditText>(R .id.etPassword).text.toString()
            startSound()
            signUpUser(username, password)
        }


        // Setting up onCLickListeners for Skip and Explore buttons
        findViewById<Button>(R.id.btnSkipLogin).setOnClickListener {
            startSound()
            goToBrowseActivity()
            Toast.makeText(this, "User skip login as a visitor", Toast.LENGTH_SHORT).show()
        }
    }

    override fun startSound() {
        super.startSound()
        if (mp == null) {
            mp = MediaPlayer.create(this, R.raw.sample)
        }
        mp?.start()
    }
//    private fun startSound() {
//        if (mp == null) {
//            mp = MediaPlayer.create(this, R.raw.sample)
//        }
//        mp?.start()
//    }

    private fun signUpUser(username: String, password: String) {
        val user = ParseUser()  // Create the ParseUser
        user.setUsername(username) // Set fields for the user to be created
        user.setPassword(password)
        val colArray = JSONArray()  // Creating empty JsonArray for collections
        user.put("collections", colArray)  // Set custom properties

        user.signUpInBackground { e ->
            if (e == null) {
            //User has successfully created the account
                Log .i(TAG, "Successfully Logged-in")
                goToMainActivity()
                Toast.makeText(this, "Signed Up Successfully!", Toast.LENGTH_SHORT).show()
            } else {
                Toast.makeText(this, "Error in Signing Up. Please try again", Toast.LENGTH_SHORT).show()
                e.printStackTrace()
            }
        }
    }

    private fun loginUser(username: String, password: String) {
        //makes the call in the background
        ParseUser.logInInBackground(username, password) { user, e ->
            if (user != null) {
                Log .i(TAG, "Successfully Logged-in")
                goToMainActivity()
                Toast.makeText(this, "Successfully Logged-in", Toast.LENGTH_SHORT).show()
            } else {
                e.printStackTrace()
                Toast.makeText(this, "Error Logging in", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun goToMainActivity() {
        val intent = Intent(this@LoginActivity, MainActivity::class.java)
        startActivity(intent)
        if (ParseUser.getCurrentUser() != null) {
            finish()                //closes the login activity, avoiding going back to login page on clicking back
        }
    }


    private fun goToBrowseActivity() {
        val intent = Intent(this@LoginActivity, BrowseActivity::class.java)
        startActivity(intent)
        finish()
    }


    companion object{
        val TAG = "LoginActivity"
    }
}