# COM SCI 118 - Fall '22 - Varghese

[TOC]

## Lecture 1: Introduction and Layering

- Is Networking Just Plumbing?
  - No, it's the new computational bus
    - Large tech companies have observed that even marginally slower network latencies will turn users away
  - And the new agile battlefield network
    - More stable communication during wartime
  - And still the world's communication channel
    - Infrastructure's reliance on the cloud => extremely strict reliability requirements
- So Why Study Networking?
  - Because it's already part of your life: the computational bus for services you need and the communication channel to stay connected
  - Because it's the hip place to be :)
- Packet Switching
  - In the early days, if two computers wanted to talk to each other, they would reserve megabits across connections
  - Len Kleinrock saw that this method produced very "bursty" traffic
    - Suggested the multiplexing of data, broken up into smaller units called packets
      - Post office model
      - More efficient sharing of data theoretically
  - Donald Davies showed how packets would produce easier reliability
    - If packet `B` gets dropped, you only need to resend `B`
  - Paul Baran showed how packets can make the system more robust
    - If a network path becomes unusable, data can still be sent
- Hat Transfer Analogy
  - The analogy:
    - Hazel's Hat => application
    - Bigwig => TCP
    - Post office => IP
    - Individual carriers => physical
  - Deeper issues with the analogy:
    - Equivalents of immigration and customs?
      - Security/authentication/etc.
    - Equivalents of postage?
      - Fixed amount of bandwidth from your ISP, which you can use to send data
      - Not charged per unit (bit)
    - Chopping up hats into slices as in data link?
      - Physical links are very narrow and constrained in size => leads to disassembly and reassembly
    - Out-of-band vs. in-band communication between layers
- Anatomy of a Web Transfer
  - End Device Networking
    - A typical laptop:
      - CPU
      - CPU Bus
      - Monitor
      - Main memory
      - Disk
      - Ethernet and wireless interface
  - IP Routing
    - System:
      - Sender domain
      - Internet service provider
      - Receiver domain
    - Forwarding: routers forward packets based on looking up destination addresses in a forwarding table
      - The real-time process – you get ~5ns to forward a packet upon receiving it
    - Routing: routers work together to build a forwarding table
      - OSPF (within domains) and BGP (between ISPs)
      - Time scale is closer to being on the order of milliseconds
- Layering More Formally
  - Layering
    - Recall that in the Hazel's Hats analogy, we simplified a complex task (transferring hats) by outsourcing reliable transmission to an import-export agency who in turn outsourced package delivery to the post office who in turn oursourced single-hop package transmission to a carrier, etc.
    - Similarly, in networking, an email transfer is simplified by subcontracting reliable delivery to transport like TCP who subcontracts packet delivery to the network layer who subcontracts to the data link etc.
    - This division of labor in networking is called layering; each horizontal slice (layer) is given a number, starting with 1 for physical, 2 for data link. etc.
      - While TCP only uses the bottom 4 layers, the most general model is the OSI/ISO model
  - The OSI Model
    - Dated but conceptually useful
    - Application => presentation => session => transport (TCP) => network (IP) => data link (Ethernet) => physical
      - Transport: segments
      - Network: packets
      - Data link: frames
      - Physical: bits/symbols
  - Layering Concepts
    - Protocol: rules governing horizontal communication between peer layer entities
    - Interface: rules governing vertical communication between a layer `N` entity and a layer `N+1` entity on the same computer
    - PDU: Protocol Data Units are the messages that are exchanged between peer entities
      - `N`-PDU between layer `N`-entities
      - On the Internet: a TPDU is a segment, an NPDU is a packet, and a DPDU is a frame
    - SDU: data unit passed across an interface
      - `N`-SDU is passed to and from layer `N` from layer `N+1`
    - PDU vs. SDU: normally `N`-PDU is `N`-SDU together with a layer `N` header
      - However, one SDU can be split into multiple PDUs if the protocol allows only small PDUs
    - Watch those headers!
      - Communication between layer entities shares physical medium by using a layer header for each layer in each message
        - Think of data in envelope with transport header, stuffed in envelope with routing header, stuffed in envelope with data link header
      - Sharing headers saves postage and also trivially coordinates headers with corresponding data (compared to out-of-band transmission between headers)
      - Strict layering: each layer only looks at its header and interface data to do its job
        - Software engineering: changes to one layer do not cause other layers to be reimplemented
        - Information can be passed between layers via interface
      - As data moves down the layers, each layer adds its header
      - As data moves up the layers, each layer strips off its header
  - The Hourglass Model
    - There's a huge variety of options at the application/transport layer and at the data link/physical layer, but a single interface at the network layer (IP)
      - Also limited at the transport layer (TCP vs. UDP)
- The IP Abstractions
  - Each layer provides a service to the layer above it
  - TCP is the abstraction of two bidirectionally-connected queues
    - One machine writes to the queue and the other reads from the queue
    - Abstracts away the lower levels
  - Routing is the abstraction of finding a route that the data will travel through



## Lecture 2:

- 