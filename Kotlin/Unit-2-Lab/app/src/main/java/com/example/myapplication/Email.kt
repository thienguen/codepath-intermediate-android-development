package com.example.myapplication

data class Email(
    val sender: String,
    val title: String,
    val summary: String,
    val isRead: Boolean
) {
}