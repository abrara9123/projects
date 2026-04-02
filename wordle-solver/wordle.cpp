#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "bstset.h"
#include "include/worldle.h"

using namespace std;

/**
 * Given a filename that contains a list of words (one word per line),
 * returns a set that contains all the words in the file.
 */
BSTSet<string> load_words(const string& filename) {
  // TODO_STUDENT
  string word;
  ifstream iff(filename);
  BSTSet<string> wordset;
  while (getline(iff, word)) {
    wordset.insert(word);
  }
  return wordset;
}

/**
 * Given a `guess` and the potential `winning_word`, computes the pattern
 * that Wordle would give us, as a string in which each character
 * corresponds to the character position on the original string and the
 * colored feedback is output in numbers as:
 *
 * - 0 - Gray
 * - 1 - Yellow
 * - 2 - Green
 *
 * For example:
 * - `get_pattern("RAISE", "SCORE") == "10012"`
 * - `get_pattern("MERRY", "CORER") == "01210"`
 */

/// Go over and review that TA said in more detail so i fully undertand this for
/// the test
string get_pattern(const string& guess, const string& winning_word) {
  // TODO_STUDENT
  string newStr = "00000";
  bool countDupe[5] = {false, false, false, false, false};
  bool winWord[5] = {false, false, false, false, false};
  for (int i = 0; i < guess.size(); i++) {
    if (guess[i] == winning_word[i]) {
      newStr[i] = '2';
      countDupe[i] = true;
      winWord[i] = true;
    }
  }
  for (int i = 0; i < guess.size(); i++) {
    for (int j = 0; j < guess.size(); j++) {
      if (guess[i] == winning_word[j]) {
        if (!countDupe[i] && !winWord[j]) {
          newStr[i] = '1';
          countDupe[i] = true;
          winWord[j] = true;
          break;
        }
      } else if (guess[i] != winning_word[i]) {
        continue;
      }
    }
  }
  return newStr;
}
/**
 * Given the current `remaining_words`, keep only the words that conform
 * to the given `feedback`, based on the given `guess`.
 *
 * For example:
 * If `remaining_words` contains {"BASIC", "SONIC", "TONIC", "STOIC"}, then:
 *
 * - `filter_words(remaining_words, "BASIC", "00122") will erase `"BASIC"` and
 * `"TONIC"` from `remaining_words`.
 *
 * In this case, the `feedback` says that the word should have an 'S' (not in
 * the middle position), therefore we filter out "TONIC". It also says that it
 * doesn't have an 'A' nor a 'B', so we filter out "BASIC". Given the
 * `feedback`, "STOIC" and "SONIC" are still possible winning words that
 * remain in `remaining_words`.
 */
void filter_words(BSTSet<string>& remaining_words, const string& guess,
                  const string& feedback) {
  // TODO_STUDENT
  vector<string> words;
  remaining_words.begin();
  string val;
  while (remaining_words.next(val)) {
    string patterval = get_pattern(guess, val);
    // cout << patterval << endl;
    if (patterval != feedback) {
      words.push_back(val);
    }
  }

  for (auto a : words) {
    remaining_words.erase(a);
  }
}

/**
 * Given a set of words that are still playable, returns
 * the word that maximizes the entropy.
 */
string recommend(BSTSet<string>& remaining_words) {
  // TODO_STUDENT
  string val;
  string retWord;
  double max = -1;
  remaining_words.begin();
  double calc = entropy(val, remaining_words);
  while (remaining_words.next(val)) {
    double calc = entropy(val, remaining_words);
    if (calc > max) {
      max = calc;
      retWord = val;
    }
  }
  return retWord;
}

// ###############################################################################

/**
 * Computes the entropy of a candidate `guess`, given the
 * `remaining_words` that are still available to play.
 *
 * This implementation will be given to the students.
 */
double entropy(const string& guess, const BSTSet<string>& remaining_words) {
  unordered_map<string, int> pattern_counts;
  BSTSet<string> copy_remaining_words = remaining_words;

  copy_remaining_words.begin();
  string word;
  while (copy_remaining_words.next(word)) {
    string pattern = get_pattern(guess, word);
    pattern_counts[pattern]++;
  }

  double entropy = 0.0;
  double total = remaining_words.size();

  for (auto [pattern, count] : pattern_counts) {
    double p = (double)count / total;
    entropy -= p * log2(p);
  }

  return entropy;
}

/**
 * Given a set of words will continually recommend one based on the
 * principle of maximizing entropy.
 *
 * After each recommendation, user is responsible to enter the feedback
 * they got from playing a Wordle word in a Wordle game engine.
 *
 * Will stop once the user notifies that they won the Wordle game.
 *
 * This implementation will be given to the students.
 */
void recommender(BSTSet<string>& remaining_words) {
  string user_feedback = "00000";
  int num_guesses = 0;
  string winning_messages[6] = {"Genius",   "Magnificent", "Impressive",
                                "Splendid", "Great",       "Phew"};

  while (!remaining_words.empty()) {
    string guess = recommend(remaining_words);
    cout << "Recommended guess: " << guess << endl;
    cout << "Enter feedback (2 for green, 1 for yellow, 0 for gray): ";
    string feedback;
    cin >> feedback;
    num_guesses++;

    if (feedback == "22222") {
      if (num_guesses <= 6) {
        cout << winning_messages[num_guesses - 1] << "! You won in "
             << num_guesses << " guesses!" << endl;
      } else {
        cout << "Sorry I made you lose :(" << endl;
      }
      break;
    }

    filter_words(remaining_words, guess, feedback);
    cout << "Remaining words: " << remaining_words.size() << endl;
    cout << "------------------------------------\n" << endl;
  }

  if (remaining_words.empty()) {
    cout << "Wait, we ran out of words!?!? This shouldn't have happened... "
            "SMH."
         << endl;
  }
}