alphabet = 'abcdefghijklmnopqrstuvwxyz'
text_input = input('Enter text: ')
possible_keys = len(alphabet)
for keys in range(possible_keys):
    decrypted_text = ''
    for character in text_input:
        if character in alphabet:
            position = alphabet.find(character)
            possible_pos = position - keys
            possible_pos %= len(alphabet)
            new_character = alphabet[possible_pos]
            decrypted_text += new_character
        else:
            decrypted_text += character
    print(f' Key#:{keys}: {decrypted_text}')
