package com.example.project6bitfitpart2

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "bitfit_table")
data class BitFitEntity(
    @PrimaryKey(autoGenerate = true) val id : Long = 0,
    @ColumnInfo(name = "itemName") val itemName: String?,
    @ColumnInfo(name = "calories") val calories: String?
)