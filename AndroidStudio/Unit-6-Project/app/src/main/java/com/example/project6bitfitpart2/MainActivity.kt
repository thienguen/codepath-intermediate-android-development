package com.example.project6bitfitpart2


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.fragment.app.Fragment
import com.google.android.material.bottomnavigation.BottomNavigationView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val recordFragment: Fragment = FoodRecordFragment()
        val dashboardFragment: Fragment = DashboardFragment()
        val addEntryFragment: Fragment = AddEntryFragment()

        val bottomNavigationView: BottomNavigationView = findViewById(R.id.bottomNavigationView)

        bottomNavigationView.setOnItemSelectedListener { item ->
            lateinit var fragment: Fragment
            when (item.itemId) {
                R.id.Record -> fragment = recordFragment
                R.id.Dashboard -> fragment = dashboardFragment
                R.id.AddEntry -> fragment = addEntryFragment
            }
            replaceFragment(fragment)
            true
        }

        bottomNavigationView.selectedItemId =R.id.Record
    }

    private fun replaceFragment(fragment: Fragment) {
        val fragmentManager =supportFragmentManager
        val fragmentTransition = fragmentManager.beginTransaction()
        fragmentTransition.replace(R.id.content, fragment)
        fragmentTransition.commit()
    }
}