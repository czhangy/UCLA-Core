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



## Lecture 3: Clock Recovery

- Bandwidth and the Shannon Bound (cont.)

  - Higher bit rate => higher frequency wave
    - Note that, roughly, bit rate = frequency
  - What does this intuition tell us?
    - A higher bit rate (each bit lasts a smaller time) leads to a higher frequency wave
    - We must cover a range of frequencies to adapt to any bit pattern
  - From Nyquist to Shannon
    - If we have a bandwidth of `B`, we can send `2B` signals per second
    - Each signal can be multilevel => these levels must be spaced apart to distinguish between them

- Clock Recovery

  - Main idea: receivers learn when to sample the continuous wave received from sender by cueing on transitions

  - Recall:

    - Sending bits is a three-step process:
      - Take an input stream of bits (digital)
      - Modulate some physical media to send data (analog)
      - Demodulate the signal to retrieve bits (digital)

  - What does the physical layer do?

    - A possibly faulty, single-hop, bit pipe that connects a sender to possibly multiple receivers
    - Morse Code analogy:
      - Example bit pipe: sending Morse Code to receivers using a flashlight
      - Issues:
        - Fundamental limits: brain-eye system processing limits leads to Inter Symbol Interference
        - Media issues: flashlight, semaphore
        - Coding: Morse Code, getting in sync, knowing receiver rate
    - Sublayers:
      - Input stream => coding sublayer => coded stream => media transmission sublayer => input signal => signal transmission sublayer => output signal => media reception sublayer => coded stream => decoding sublayer => output stream

  - Sampling Bits

    - Receivers recover the bits in the input signal by ssmpling output signal close to middle of bit period
    - Two limits to bit rate: channel bandwidth (Nyquist) and noise (Shannon)

  - Main Topic

    - How does a receiver know when to sample bits, and how can the sender help?
    - By cueing on transitions ensured by sender sending "extra bits"

  - Who needs a clock anyways?

    - How to initially synchronize receiver clock with sender clock?
      - Initial training bits
    - Stay in sync (first cut): receiver has a very similar clock as sender (say both run at 1GHz)
    - Problem: all real physical clocks drift over time
      - Crucial at high speeds
      - Small drift leads to sampling error
      - How do we keep in sync?
        - Transitions

  - Transitions and Coding

    - Example: parse: "nohewontgosoon"
      - Need spaces and punctuations to parse speech
    - Stream of bits without transitions (change in signal value) is equally hard to parse
    - Real data may contain all `0`s, so how w can you ensure transitions?
      - Coding => adds cost
    - Code to ensure that every `n` bits, you get at least `m` transitions
      - Different coding schemes parameterized by `m` and `n`

  - Asynchronous Coding

    - Codes a character (assume 8 bits in ASCII)
    - We add "extra" start bits to get into sync and one or two stop bits
      - `1` is encoded as high voltage, `0` as low

  - Receiver code assumes:

    - Edge detector: a hardware gadget used to tell whether a `0` goes to a `1` or a `1` to a `0` that we abstract as a function to tell where a transition is

    - Sampling: we abstract sampling and compare it to a threshold as a function `SampleSignal`

    - Clock drift: receiver has a clock that runs at approximately the same rate as sender

    - ```pseudocode
      Data Structures:
      C[0..10]; ARRAY, to store bits in current character
      
      On Transition:
      	StartTimer(1/2 bit) // Don't sample on an edge
      	For (i = 0 to 10), do
      		Wait(TimerExpiry);
      		C[i] = SampleSignal;
      		StartTimer(1 bit) // Wait for next bit
      	End;
      	If (C[0] = 1) and (C[9] = C[10] = 0) then Output C[1..8];
      ```

  - Slow Clock Problem

    - How much slower can the receiver clock be without causing bit errors? => 5%
    - Can drift by 50% per bit => 10 bits => 5% drift per bit

  - Synchronous Transmission

    - Lots of start bits (preamble) + up to 12000 bits + lots of stop bits (postamble)
    - Same as asynchronous except larger frame sizes
    - Requires better clock tolerance and more sophisticated coding

  - Why Synchronous Transmission?

    - For clock recovery, receiver must know when to start its receive clock (phase)
      - Then can sample the line at periodic intervals at the same rate as sender clock with some help from transitions in data
    - In asynchronous, receiver gets locked in phase when voltage goes from low to high (start bit)
      - Need to have fairly large idle time between characters for receiver to get locked in phase for each character
      - Slows transmission and limits it to low rates
    - Two overheads for start bit: extra bit + extra time needed for reliable detection
      - Starting up receiver clock is expensive
    - In synchronous, we put a large number of start bits at the front of a large number of data bits
      - Allows the start-up overhead to be amortized

  - Manchester Encoding

    - Signal to data:
      - High to low transition (`10`) => `1`
      - Low to high transition (`01`) => `0`
    - Comments:
      - Solves clock recovery problem
        - Transitions re-sync clocks every time they occur
      - Only 50% efficient (1/2 bit per transition)
      - Still need preamble (typically `0101010101...`) with a trailing `11` in Ethernet
    - Getting Locked in Phase
      - In asynchronous, you get in phase by a single `0` to `1` transition
        - Not very reliable in the presence of noise
      - But in Manchester, a sequence of `0`s sent can be read off as a sequence of `1`s if the receiver is out of phase
      - In Manchester, you get in phase by sending a preamble or group of start bits of the form `01` repeating, in which the only transitions are at mid-bit
        - Easy to recognize and get locked in phase
        - End with `11` to know where data starts
        - Full preamble is `0101010101...11`
        - Can't count because we don't know how long the receiver will take to get in phase => once it's in phase, it can watch out for the `11`

  - Phase Locked Loops

    - Once you lock in at the start of a data unit, you can rely on accuracy of receiver clock frequency (as in asynchronous)
      - Can't do this if the data unit is large
    - Could try resetting receiver clock on every observed transition
      - Susceptible to noise
      - Better to use more gradual adjustment
    - Phase locked loops measure phase difference and speed up or slow down the receiver clock to reduce phase difference
      - Commonly used

  - Modern Codes

    - 8-10 coding: every group of 8 data bits is encoded as 10 bits
      - Easily done by table lookup
      - Removes bit patterns with no transitions
      - Look up tables get too big if we try to go higher
    - Why transitions?
      - Because all 10-bit patterns with no transitions (`0000000000` and `1111111111`) are not used
      - In fact, we can rule out even patterns with 1 transition as we have 1024 patterns to code a byte
    - Receiver decoding: a 1024 entry table that looks up the 8-bit data corresponding to each received 10-bit pattern

  - What Makes a Code Good?

    - Coding efficiency: real bits/coded bits
    - Signal-to-noise ratio
    - DC balance
    - Implementation complexity

  - Eye Patterns

    - A way to superimpose arbitrary bit sequences on screen as opposed to sending them in parallel
    - In a perfect system, we will have a well-defined eye
      - Should sample at the center of the eye
      - Nice visual test of line quality

  - Broadband Coding

    - Baseband coding uses energy levels such as voltage or light
      - In broadband coding, information is modulated on a carrier wave of a certain frequency
      - Used by modems
    - Modulation refers to changing the properties of the carrier to communicate the required information
      - Frequency Shift Keying: high frequency encodes a `1`, low encodes a `0`
      - Amplitude Shift Keying: high amplitude encodes a `1`
    - Baseband vs. Broadband
      - Baseband modulation: send the "bare" signal
      - e.g., +5V for `1`, -5V for `0`
      - All signals fall in the same frequency range
      - Broadband modulation
        - Use the signal to modulate a high-frequency signal (carrier)
        - Can be viewed as the product of two signals
    - Digital Modulation Methods
      -  Amplitude Shift Keying (ASK)
      - Frequency Shift Keying (FSK)
      - Phase Shift Keying (PSK)

  - Summary

    - Clock synchronization: getting receiver clock in sync with sender transmission using transitions guaranteed by a code
    - Coding schemes: asynchronous (transitions at start and end, small number of bits) vs. synchronous (many transitions in start and guaranteed transitions in data as well)
    - Real engineering: phase locked loops (not programs we used), and eye patterns to visualize
    - Broadband coding: modulate `1`s and `0`s on a high frequency carrier wave in wireless and cable modems



## Lecture 4:

- 