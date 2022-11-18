package com.example.simplewishlist

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [FoodEntity::class], version = 1)
abstract class AppDatabase : RoomDatabase()
{
    abstract fun foodDao() : FoodDao

    companion object
    {
        @Volatile
        private var INSTANCE : AppDatabase? = null

        fun getInstance(context : Context) : AppDatabase =
            INSTANCE ?: synchronized(this)
            {
                return INSTANCE ?: buildDatabase(context).also { INSTANCE = it }
            }

        private fun buildDatabase(context : Context) =
            Room.databaseBuilder(
                context.applicationContext,
                AppDatabase::class.java,
                "food.db"
                ).build()
    }
}