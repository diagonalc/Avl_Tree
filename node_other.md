# Other Notes

### Note about header files  
Including a header is basically copying everything inside the header and pasting it into where you include it.   

What a header should include: declarations, structures  
What a .c file should include: functions, macros, variables

Why a header file shouldn't include complete functions?  
As if two .c files included the header, the function will be defined twice, leading to error.  

Then why structures can be included in a header file?  
Structures can be defined twice in **different** .c file. Meanwhile, header guard (```#ifndef```,  ```#endif```) can prevent repeated defination of a structure in one .c file. 

---

### RSA Algorithm
RSA algorithm is a kind of asymmetric encryption algorithm. It allows others to encode the msg with the public key, while you are the only one who possesses the private key to decrypt it. 
#### Euler Function
For a positive integer  $n$, $\phi(n)$ equals to the number of positive integers less than or equal to $n$ that are coprime (two numbers that don't share a common factor other than 1) to each other.\
The Euler Function states that for two prime numbers $p$ and $q$, 
$$\phi(n) = (p - 1)(q - 1)$$
(Proof of Euler Function: https://www.bilibili.com/video/BV1vdcDehEyg/?spm_id_from=333.337.search-card.all.click&vd_source=0602a2856d1cb8214f611b0037ba4cd6)

#### Generating public and private keys
General flow:\
```pick p and q --> calculate φ(n) --> pick e --> calculate d```

#### 1. Choosing two large prime numbers $p$ and $q$ randomly   
#### 2. Calculating $n$ and $\phi(n)$:
$$n = p*q$$ 
$$\phi(n) = (p-1)(q-1)$$
#### 3. Choosing the public key $e$:
Choose $e$ in the range of $1<e<\phi(n)$ that is coprime to $\phi(n)$ 
#### 4. Calulating the private key $d$:
Compute the modular inverse of $e$ modulo $\phi(n)$, denoted as $d$, such that $e \cdot d \equiv 1 \pmod{\phi(n)}$
$$d = \frac{k\phi(n)+1}{e}$$
$k$ can be any integer, as long as the result $d$ is integer\

#### Encryption and decryption
if the someone want to send a message, denoted as $m$ to the receiver:
|  Stage  | Expression   | Description   |
| ----- | ----- | ----- |
| Encryption | $c\equiv m^e \pmod{n}$ | the sender use the public key $e$ (encoder) to compute cypher $c$|
| Decryption | $m\equiv c^d \pmod{n}$ | the receiver use the private key $d$ (decoder) to compute message $m$|

