
WORD_FILE = '/home/jml/src/Scrabble/source_data/sowpods.txt'
#WORD_FILE = '/usr/share/dict/words'

def generate_words():
    fd = open(WORD_FILE, 'r')
    for line in fd:
        yield line.strip().lower()
    fd.close()


WORD_LIST = set(generate_words())


def fits_target(target_word, central, word):
    if not 4 <= len(word) <= target_word:
        return False
    if central not in word:
        return False
    duplicate = list(target_word)
    for c in word:
        if c not in duplicate:
            return False
        duplicate.remove(c)
    return True


def is_plural(word):
    if word[-1] != 's':
        return False
    return word[:-1] in WORD_LIST


def search_dictionary(target_word, central):
    for word in WORD_LIST:
        if fits_target(target_word, central, word) and not is_plural(word):
            yield word


def main(target_word, central):
    count = 0
    for word in search_dictionary(target_word, central):
        count += 1
        print word
    print "%d solutions found." % (count,)


if __name__ == '__main__':
    import sys
    if len(sys.argv) != 3:
        print 'target.py <target_word> <central_character>'
        sys.exit(2)
    if len(sys.argv[1]) != 9:
        print 'target_word must have exactly 9 letters.'
        sys.exit(2)
    if len(sys.argv[2]) != 1:
        print 'central_character must have exactly 1 letter.'
        sys.exit(2)
    main(sys.argv[1], sys.argv[2])
