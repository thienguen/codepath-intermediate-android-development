package com.example.simplewishlist

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "fitbit_table")
data class FoodEntity (
    @ColumnInfo(name = "Food") val name: String,
    @ColumnInfo(name = "calories") val calories: String,
    @ColumnInfo(name = "time") val time: String,
    @PrimaryKey(autoGenerate = true) val id: Long = 0
)
