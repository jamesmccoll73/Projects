## secretMessages:

**Function:** Uses rsa encryption and decryption to pass secret messages through files 

**Explaination of the Commands** 
ENCRYPT [filename] [n] [message]: Creates a file at the specified path, writing an encrypted version of [message]. [n] is an integer which is used in the encryption process.

DECRYPT [input] [output]: Opens the file at [input], reads the contents of the file, decrypts the message, and overwrites the contents of the file at [output] with the decrypted message.

**Example Walkthrough of Encryption/Decryption:** <br />
./rsa 837 839  
    -> 1) p value for rsa encryption
    -> 2) q value for rsa encryption

ENCRYPT input1.txt 702243 this is my line of code
    -> 1)the file to transfer the encrypted message into
    -> 2)n value for rsa encryption (should be p*q)
    -> 3)message to be encrypted 

**Contents of input1.txt after encryption
    -> 457696 329878 345629 476479 276634 563625 220590 139293

DECRYPT input1.txt output2.txt
    -> 1)file to be decrypted
    -> 2)created file where the decrypted message will be stored

**Contents of output1.txt after decryption
    -> this is my line of code

