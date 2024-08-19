# American Express uses 15-digit numbers, start with 34 or 37
# MasterCard uses 16-digit numbers, start with 51, 52, 53, 54, or 55
# Visa uses 13- and 16-digit numbers, start with 4.


card = input("Number: ")
copycard = card[::-1]

checksum = sum(int(x)*2 // 10 + int(x)*2 %
               10 for x in copycard[1::2]) + sum(int(x) for x in copycard[::2])

if checksum % 10 == 0:
    if len(card) == 15 and (int(card[0:2]) in [34, 37]):
        print("AMEX")
    elif len(card) == 16 and 50 < int(card[0:2]) < 56:
        print("MASTERCARD")
    elif len(card) in [13, 16] and int(card[0]) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
