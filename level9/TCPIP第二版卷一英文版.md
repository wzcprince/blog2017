

# ch02 The Internet Address Architecture

## 2.4 CIDR and Aggregation
### 2.4.1 Prefixes

### CIDR

- Using CIDR, any address range is not predefined as being part of a class but instead
requires a mask similar to a subnet mask, sometimes called a CIDR mask

- a scheme similar to VLSM
	- 与VLSM的区别在于 CIDR masks are not limited to a site but are instead visible to the global routing system. 

- network number 和CIDR mask 的combination就叫做  network prefix 
	- used for both IPv4 and IPv6 address management


# ch07 Firewalls and Network Address Translation (NAT)

## 7.2.Firewalls

# ch11 Name Resolution and the Domain Name System (DNS)

## 11.4 DNS Caching



# ch18 
### 18.4.7.Nonces and Salt

- nonce 
A cryptographic **nonce** is a number that is used once (or for one transaction) in acryptographic protocol. Most commonly, a nonce is a random or pseudorandom number that is used in authentication protocols **to ensure freshness**. Freshness is the (desirable)property that a message or operation has taken place in the very recent past. For example, in a challenge-response protocol, a server may provide a requesting client with a nonce, and the client may need to respond with authentication material as well as a copy of the nonce(or perhaps an encrypted copy of the nonce) within a certain period of time. This helps **to avoid replay attacks**, because old authentication exchanges that are replayed to the server would not contain the correct nonce value.

- salt 
 A **salt** or salt value, used in the cryptographic context, is a random or pseudorandom number used to frustrate['frʌstret]阻挠挫败 **brute-force attacks** on secrets. Brute-force attacks usually involve repeatedly guessing a password, passphrase, key, or equivalent secret value and checking to see if the guess was correct. Salts work by frustrating the checking portion of a brute-force attack. The best-known example is the way passwords used to be handled in the UNIX system. Users’ passwords were encrypted and stored in a password file that all users could read. When logging in, each user would provide a password that was used to double encrypt a fixed value. The result was then compared against the user’s entry in the password file. A match indicated that a correct password was provided.



