package com.example.simplewishlist

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.simplewishlist.databinding.ActivityMainBinding as ActivityMainBinding1

class MainActivity : AppCompatActivity()
{
    private lateinit var binding: ActivityMainBinding1
    private lateinit var wishListViewModel: WishListModel

    override fun onCreate(savedInstanceState: Bundle?)
    {
        // Create ActivityMainBiding
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        binding = ActivityMainBinding1.inflate(layoutInflater)
        setContentView(binding.root)
        wishListViewModel = ViewModelProvider(this)[WishListModel::class.java]

        // Everytime we click on the submitButton, we will have a new Wishlist,add in the RvView
        binding.submitButton.setOnClickListener {
            NewWishList(null).show(supportFragmentManager, "NewWishList")
        }

        // After receiving the WishList data fetched, set it via adapter
        setRecyclerView()
    }

    private fun setRecyclerView()
    {
        val mainActivity = this

        wishListViewModel.wishList.observe(this){
            binding.rvWishList.apply {
                layoutManager = LinearLayoutManager(applicationContext)
                adapter = WishListAdapter(it)
            }
        }
    }
}