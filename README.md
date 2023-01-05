# SatoshiNakamoto 🥷

# Members
* Salaj Rijal
     
# A statement of the problem you are solving and/or a high level description of the project.
I will be creating my own blockchain (hopefully cryptocurrency). I will be starting small and then working my way up from there. The MVP is a single process blockchain that feeds information to user interface in a seperate process. I will then add these features incrementally:
- Keep track of transactions in blockchain.
- Create a peer-to-peer network where multiple processes maintain concesensus on blockchain

# A description as to how the project will be used (describe the user interface).
The user will interact with the blockchain through a user interface. For the MVP the user interface only displays data but for later phases the user will be allowed to request transactions or check balance.

# A description of your technical design. This should include:

**Topics Covered**   
The MVP will cover these topics:
- Allocating memory
    - Memory will have to be allocated
- Working with files
    - The blockchain will be stored in a file
- Processes
    - At the start, the program will split into two processes. One being the user interface, the other one being the blockchain.
- Pipes
    - The blockchain and user interface will use a pipe to communicate with eachother

If I get to the additional phases, these topics will be covered as well:
- Sockets
    - The peer-to-peer network will use sockets to communicate with eachother

**How you are breaking down the project and who is responsible for which parts.**
<br>I will be doing everything
  
**What algorithms and /or data structures you will be using, and how.**
- Sha256: to hash the blocks (will find library to do it online)
- Blockchain: to have public ledger of cryptocurrency
- RSA: to make sure only person w/ private key can send transactions. (If this is too hard to implement I will omit) 

# A timeline with expected completion dates of parts of the project.

Estimate: 01/08
* MVP: Simple Blockchain
    - Hash block (will find hashing library)
    - Add block
    - Validate block
    - Validate blockchain
    - Mine block

Estimate: 01/13
* Phase 2: Implementing Cryptocurrency
    - Transaction pool
    - Validate transaction (might or might not use RSA signing)
    - User interface add transaction
    - User interface query balance for user (which will have key)

Estimate: 01/
* Phase 3: Peer To Peer Network
    - Send history of blockchain to new clients
    - Send new transactions to other clients
    - Add blocks as other nodes send them
    - 
