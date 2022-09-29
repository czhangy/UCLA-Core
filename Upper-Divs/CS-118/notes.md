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



## Lecture 2: Limits to Transmission

- Review

  - The physical layer is responsible for transporting individual bits
  - The data link layer allows us to include headers
  - The IP layer routes from source to location
  - The TCP layer packetizes and sends from a sender queue to a receiver queue
    - Packetizes => takes the byte stream and breaks it up into smaller chunks
    - Promotes reliability through acknowledgements and guarantee that everything that has been sent is read
  - Headers
    - TCP header contains the payload packet and a sequence number
    - IP header contains the origin and destination IP addresses
    - The data link header contains the origin and destination MAC addresses
      - MAC address is one interface of the router => location independent
        - IP addresses are location dependent
      - `yx` => to MAC address `y` from `x`
    - Headers are stripped away at each corresponding letter
  - Strict Layering
    - Each layer only looks at its header and interface data to do its job
      - Modularity
      - Information can be passed between layers via interface
    - As data moves down the layers, each layer adds its header; as data moves up, each layer strips off its header
  - In Class Example:
    - `S` (Sender) => Sender TCP => Sender IP => Sender Data Link => Router Data Link => Router IP => Router Data Link => Receiver Data Link => Receiver IP => Receiver TCP => `R` (Receiver)
    - Only the data link information changes from sender to receiver

- Limits to Transmission

  - Main idea: there are limits to the speed at which bits can be transmitted between a sender and a receiver over a channel based on how fast the channel can react (bandwidth) and the noise

  - Physical Layer Abstraction

    - Sending a bit over a channel
      - How fast can we transmit?
      - How do we decide when to sample?
      - How do different forms of media impact this transmission?

  - The Foundation: Sending Bits

    - A three-step process:
      - Take an input stream of bits (digital data)
      - Modulate some physical media to send data (analog)
      - Demodulate the signal to retrieve bits (digital again)
    - No boundaries at the physical layer => boundaries at the data link layer

  - Now in More Detail

    - We will divide the physical layer into sublayers, starting with a coding layer (semaphores have codes as well)
      - The bottom sublayer is really describing the essential properties of the media (frequency response, bit error rate)
      - The middle sublayer describes properties of particular media (e.g., satellites, coaxial cable, fiber, etc.)
      - The top sublayer is about things like clock recovery, synchronization, etc.
    - To understand the Shannon Limit, we have to understand what bandwidth means in Hz (EE idea) and why it's related to bandwidth in bits/sec (CS idea)
    - To do so we need to take a small painless detour into the world of signals, systems, and Fourier Analysis

  - Bottom Sublayer: Signal Transmission and Limits

    - How fast can you send, and what prevents you from sending faster?

    - Sending bits to a receiver:

      - Goal: to send a sequence of `0`s and `1`s from a sender to a receiver by sending energy (e.g., light, electricity) over a channel (e.g., fiber, cable)
        - Ex) One coding: `0` = no energy, `1` = energy
      - Problem: real channels distort input energy signals, leading to two questions:
        - How can we predict what a given channel will do to an input signal given some properties of the channel?
          - Fourier analysis
        - How does distortion affect maximum bit rate?
          - Nyquist (sluggishness) and Shannon (noise) limits

    - Signals and Channels

      - Signal: energy (e.g., voltage and light) that varies with time
        - Continuous and discrete
        - Periodic
        - Period and frequency
      - Channel: physical medium that conveys energy from a sender to a receiver (e.g., a fiber link) with possible distortion

    - Sine Waves

      - Sine waves are spvial because all signals can be rewritten in terms of sine waves

      - Mathematically:

        - $$
          A\sin(2\pi ft+\theta)
          $$

        - `A` is max value (amplitude)

        - `f` is frequence

        - `θ` is initial phase shift

      - Express angle in radians!

    - Fournier Analysis: The Big Picture

      - If we forget about noise, most channels are "nice" to sine waves
        - A sine wave of frequency `f` is always scaled by a fixed factor `s(f)` and phase shifted by a fixed amount `p(f)`, regardless of amplitude
      - Thus, we can completely describe a channel by plotting the values of `s(f)` (frequency response) and `p(f)` (phase response) for all values of frequency `f`
      - To find what happens to arbitrary signal `S`, we:
        - Use Fourier Analysis to rewrite `S` as a sum of sine waves of different frequencies
        - Use frequency and phase response to see the effect on each sine wave
        - Add scaled sine waves to find output signal

    - Bandwidth

      - A range of frequencies for which a channel passes signal through; not very precise
      - More bandwidth, more fidelity
      - More fidelity, better recovery of bits

    - Sluggishness and Noise

      - Most channels are sluggish (they take time to respond) because they turn a deaf ear to high frequencies in the input signal
        - Thus, lower bandwidth channels are more sluggish
      - What about noise?
        - Different models for different channels
        - Simplest and common model: white noise (uniformly distributed at all frequencies and normally distributed within a frequency)

    - Sampling Bits

      - Receivers recover the bits in the output signal by sampling output signal close to middle of bit period
      - Two limits to bit rate: Nyquist (channel bandwidth) and Shannon (noise)
      - When a signal is sent, the output will be a sinc wave
        - When can we send the next wave?
        - Nyquist noticed that sending every `T/2` works since the peak of the current signal lines up with the zeroes of past bits
          - Assuming bandwidth is `1/T`, the max bit rate is `2/T` or 2 times the bandwidth
        - We can play with the voltage to send more bits

    - Baud Rate and Bit Rate

      - To prevent ISI (inter-symbol interference), we cannot send "symbols" faster than `2B` times per second
        - Nyquist rate is the max rate of sending symbols, not bits (baud rate)
      - But as we saw, each symbol in a signal can carry multiple bits
      - With `L` signal levels, bit rate is `log L` times baud rate
      - Noise prevents us from transmitting many signal levels

    - The Shannon Bound

      - `S` is the maximum signal amplitude

      - `N` is the maximum noise amplitude

      - `log(S/2N)` bits per signal, `2B` signals/sec (Nyquist)

      - Naive bound is:

        - $$
          2B\log\left(\frac{S}{2N}\right)
          $$

      - Shannon bound is:

        - $$
          B\log\left(1+\frac{S}{2N}\right)
          $$

      - The real Shannon bound does not have the factor of `2` and has an extra `1` added

        - This is because our simple model was only for a simple coding and for fixed, deterministic noise

      - Shannon bound works for any coding scheme (frequency, phase modulation) and for Gaussian additive noise

        - Needs a deep probabilistic argument

  - Bit Rate vs. Frequency

    - A higher bit rate (each bit lasts a smaller time) leads to a higher frequency wave



## Lecture 3:

- 