#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const unsigned int LOOP = 10;

const string AUTHORIZED_CHAR = "RYBOP";

/*
 * TODO :
 * - improve error handling
 * - level system, w/o position indication, number of tries
 * - helper : rules and CLI arguments
 * - repetition forbidden
 */

/**
 * Get a randomized string to play with
 *
 * @param string authorizedChar String of letters possibilities
 *
 * @return string
 */
string stringToGuess(string authorizedChar);

/**
 * in_array in c
 */
bool isCharInString(char needle, string haystack);

/**
 * Returns if the mastermind's distance shows error
 */
bool hasError(string patternMatching);

/**
 * Returns the mastermind's distance between the solution and the sequence to guess
 *
 * @param string guessing String of the attempt N
 * @param string toGuess Solution
 */
string getPatternMatching(string guessing, string toGuess);

int main(int const argc, char const *argv[]) {
    cout << " ---- Mastermind ---- " << endl;
    cout << " -------------------- " << endl;
    cout << "Available colors : R(ed) Y(ellow) B(lue) O(range) P(ink)" << endl;
    cout << "Response := + : color in good position | - : color in wrong position | x : bad color" << endl;

    unsigned int attempt = 0;
    string guessing;
    string toGuess = stringToGuess(AUTHORIZED_CHAR);
    bool found = false;
    do {
        ++attempt;
        cout << "Try to guess sequence (" << attempt << "/" << LOOP << ") : " << endl;
        cin >> guessing;
        if (guessing.length() != toGuess.length()) {
            cout << "Guessing is too short or too long" << endl;
            continue;
        }
        string patternMatching = getPatternMatching(guessing, toGuess);
        if (!hasError(patternMatching)) {
            found = true;
            break;
        }

        cout << "Result : " << patternMatching << endl;
    } while(attempt < LOOP);

    if (found) {
        cout << "Congrats ! Solution " << toGuess << " was found in " << attempt << " tries." << endl;
    } else {
        cout << "Sorry, solution " << toGuess << " wasn't found." << endl;
    }

    return 0;
}

// Get a randomized string to play with
string stringToGuess(string authorizedChar) {
    string toGuess = authorizedChar;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(toGuess.begin(), toGuess.end(), default_random_engine(seed));

    return toGuess;
}

// in_array in c
bool isCharInString(char needle, string haystack) {
    for (size_t i = 0; i < haystack.length(); ++i) {
        if (needle == haystack[i]) {
            return true;
        }
    }

    return false;
}

// Returns if the mastermind's distance shows error
bool hasError(string patternMatching) {
    for (size_t i = 0; i < patternMatching.length(); ++i) {
        if (isCharInString('-', patternMatching) || isCharInString('x', patternMatching)) {
            return true;
        }
    }
    return false;
}

// Returns the mastermind's distance between the solution and the sequence to guess
string getPatternMatching(string guessing, string toGuess) {
    string patternMatching = "";
    for (size_t i = 0; i < guessing.length(); ++i) {
        if (!isCharInString(guessing[i], toGuess)) {
            patternMatching += "x";
        } else if (guessing[i] == toGuess[i]) {
            patternMatching += "+";
        } else {
            patternMatching += "-";
        }
    }

    return patternMatching;
}
