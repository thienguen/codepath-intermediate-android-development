package com.example.myapplication

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Color
import android.os.Bundle
import android.text.SpannableStringBuilder
import android.view.View
import android.view.WindowManager
import android.view.inputmethod.InputMethodManager
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.core.text.color
import nl.dionsegijn.konfetti.KonfettiView
import nl.dionsegijn.konfetti.models.Shape
import nl.dionsegijn.konfetti.models.Size

class MainActivity : AppCompatActivity() {
    private lateinit var checkNum : TextView
    private lateinit var checkCorrect : TextView
    private val wordToGuess = FourLetterWordList.getRandomFourLetterWord()

    @SuppressLint("CutPasteId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        title = "Guess the Word"
        // Setting up
        // Support variables
        val answer        = findViewById<TextView>(R.id.textView17)
        val clearEditText = findViewById<EditText>(R.id.input)
        val button        = findViewById<Button>(R.id.guess)
        val clearButton   = findViewById<Button>(R.id.resetButton)
        val congrat = findViewById<Button>(R.id.congratButton)
        var i             = 0

        answer.text       = wordToGuess
        button.setOnClickListener {
            val userInput = findViewById<EditText>(R.id.input).text.toString().uppercase()

            // Error handling
            userInput.forEach {
                if (it.isDigit()) {
                    Toast.makeText(this, "Please enter only letters", Toast.LENGTH_SHORT).show()
                    return@setOnClickListener
                }
            }

            // Error handling
            userInput.length.let {
                if (it != 4) {
                    Toast.makeText(this, "Please enter 4 letters", Toast.LENGTH_SHORT).show()
                    return@setOnClickListener
                }
            }

            hideKeyboard()
            when (i)
            {   // update the id to match the rhs
                0 -> {
                    checkNum = findViewById(R.id.textView7)
                    checkCorrect = findViewById(R.id.textView8)
                    i++
                }
                1 -> {
                    checkNum = findViewById(R.id.textView9)
                    checkCorrect = findViewById(R.id.textView10)

                    i++
                }
                2 -> {
                    checkNum = findViewById(R.id.textView11)
                    checkCorrect = findViewById(R.id.textView12)
                    answer.visibility = View.VISIBLE
                    button.isClickable = false
                    button.setTextColor(ContextCompat.getColor(this, R.color.black))
                    button.setBackgroundColor(ContextCompat.getColor(this, R.color.white))
                    Toast.makeText(applicationContext,"You have no more guess!",Toast.LENGTH_SHORT).show()
                    i++
                }
                3 -> {
                    i++
                }
            }
            // update the right hand side of our app
            // and clear text after each submission
            clearEditText.text.clear()
            checkNum.text = userInput

            val s2 = SpannableStringBuilder()
            for (k in 0..3)
            {
                if (userInput[k] == wordToGuess[k])
                {
                    s2.color(Color.GREEN) { append(userInput[k]) }
                }
                else if (wordToGuess.contains(userInput[k]))
                {
                    s2.color(Color.BLUE) { append(userInput[k]) }
                }
                else
                {
                    s2.color(Color.RED) { append(userInput[k]) }
                }
            }
            checkCorrect.text = s2

            if (!button.isClickable)
            {
                clearButton.visibility = View.VISIBLE
            }

            if (userInput == wordToGuess)
            {
                Toast.makeText(applicationContext,"You win!",Toast.LENGTH_SHORT).show()
                clearButton.visibility = View.VISIBLE
                congrat.visibility = View.VISIBLE
            }
        }

            congrat.setOnClickListener {
                val viewKonfetti = findViewById<KonfettiView>(R.id.viewKonfetti)
                viewKonfetti.build()
                    .addColors(Color.BLUE, Color.GREEN, Color.MAGENTA)
                    .setDirection(0.0, 359.0)
                    .setSpeed(1f, 5f)
                    .setFadeOutEnabled(true)
                    .setTimeToLive(2000L)
                    .addShapes(Shape.Square, Shape.Circle)
                    .addSizes(Size(12))
                    .setPosition(-50f, (windowManager.defaultDisplay.width + 50).toFloat(), -50f, -50f)
                    .streamFor(300, 5000L)
            }

            clearButton.setOnClickListener {
                finish()
                startActivity(intent)
                overridePendingTransition(0, 1)
                Toast.makeText(applicationContext,"Game Reset!",Toast.LENGTH_SHORT).show()
                clearButton.visibility = View.INVISIBLE

            }
    }

    /**
     * Parameters / Fields:
     * N/a (void)
     * Returns: Hiding the keyboard after the user has submitted their guess
     */
    private fun hideKeyboard()
    {
        val view = this.currentFocus
        if (view != null) {
            val imm = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
            imm.hideSoftInputFromWindow(view.windowToken, 0)
        }
        window.setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN)
    }

}


