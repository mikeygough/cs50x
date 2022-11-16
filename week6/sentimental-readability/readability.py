# TODO

''' Coleman-Liau index is computed as:
0.0588 x L - 0.296 x S - 15.8

L is the average number of letters per 100 words in the text
S is the average number of sentences per 100 words in the text
'''

from cs50 import get_string


def count_letters(text):
    letters = 0
    for char in text:
        if char.isalpha():
            letters += 1
    return letters


def count_words(text):
    words = 0
    for char in text:
        if char == " ":
            words += 1
    return words + 1


def count_sentences(text):
    sentences = 0
    for char in text:
        if char == "?" or char == "." or char == "!":
            sentences += 1
    return sentences


# get the text
text = get_string("Text: ")

# debugging
# print("Letters: ", count_letters(text))
# print("Words: ", count_words(text))
# print("Sentences: ", count_sentences(text))

letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

# compute L & S
L = round(((letters / words) * 100.), 2)
S = round(((sentences / words) * 100.), 2)

# compute coleman liau index
coleman_liau_index = round(0.0588 * L - 0.296 * S - 15.8, 0)

# print grade level
if coleman_liau_index < 1:
    print("Before Grade 1")
elif coleman_liau_index >= 16:
    print("Grade 16+")
else:
    print("Grade {}".format(int(coleman_liau_index)))