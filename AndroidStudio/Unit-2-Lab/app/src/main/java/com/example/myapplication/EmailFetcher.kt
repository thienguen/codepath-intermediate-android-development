package com.example.myapplication

class EmailFetcher {
    companion object {
        private val senders = listOf("Dahlia Cline", "Kevin Miranda", "Kaya Austin", "Laila Calderon", "Marquise Rhodes", "Fletcher Patel", "Luz Barron", "Kamren Dudley", "Jairo Foster", "Lilah Sandoval", "Ansley Blake", "Slade Sawyer", "Jaelyn Holmes", "Phoenix Bright", "Ernesto Gould")
        private const val title = "Welcome to Kotlin!"
        private const val summary = "Welcome to the Android Kotlin Course! We're excited to have you join us and learn how to develop Android apps using Kotlin. Here are some tips to get started."
        fun getEmails(): MutableList<Email> {
            var emails : MutableList<Email> = ArrayList()

            for (i in 0..2)
            {
                val email = Email(senders[i], title, summary, false)
                emails.add(email)
            }

            for (i in 2..9) {
                val email = Email(senders[i], title, summary, false)
                emails.add(email)
            }
            return emails
        }

        fun getNext5Emails(): MutableList<Email> {
            var newEmails : MutableList<Email> = ArrayList()
            for (i in 10..14) {
                val email = Email(senders[i], title, summary, false)
                newEmails.add(email)
            }
            return newEmails
        }
    }
}