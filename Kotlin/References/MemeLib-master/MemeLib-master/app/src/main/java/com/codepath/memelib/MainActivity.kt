package com.codepath.memelib

import android.media.MediaPlayer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import android.widget.Toast.LENGTH_SHORT
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import com.codepath.memelib.fragments.ComposeFragment
import com.codepath.memelib.fragments.FeedFragment
import com.codepath.memelib.fragments.ProfileFragment
import com.google.android.material.bottomnavigation.BottomNavigationView

class MainActivity(override var mp: MediaPlayer? = null) : AppCompatActivity(), SoundClick {
    var p_flag = 0
    var c_flag = 0

    override fun startSound() {
        super.startSound()
        if (mp == null) {
            mp = MediaPlayer.create(this, R.raw.sample)
        }
        mp?.start()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val fragmentManager: FragmentManager = supportFragmentManager

        findViewById<BottomNavigationView>(R.id.bottom_navigation).setOnItemSelectedListener {
                item ->

            var fragmentToShow: Fragment? = null

            when(item.itemId) {

                R.id.action_home -> {
                    if(p_flag == 1 || c_flag == 1) {
                        startSound()
                        p_flag = 0
                        c_flag = 0
                    }
                    fragmentToShow = FeedFragment()
                    Toast.makeText(this, "Home", LENGTH_SHORT).show()
                }
                R.id.action_profile -> {
                    startSound()
                    p_flag = 1
                    fragmentToShow = ProfileFragment()
                    Toast.makeText(this, "Profile", LENGTH_SHORT).show()
                }
                R.id.action_compose -> {
                    startSound()
                    c_flag = 1
                    fragmentToShow = ComposeFragment()
                    Toast.makeText(this, "Compose", LENGTH_SHORT).show()
                }

            }

            if(fragmentToShow != null) {
                fragmentManager.beginTransaction().replace(R.id.flContainer, fragmentToShow).commit()
            }
            true
        }

        // Set default selection
        findViewById<BottomNavigationView>(R.id.bottom_navigation).selectedItemId = R.id.action_home

    }

    companion object {
        const val TAG = "MainActivity"
    }
}