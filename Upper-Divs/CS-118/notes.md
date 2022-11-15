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



## Lecture 4: Media

- Main idea: to architect a large network, one needs to use different types of media at different places in the network

- Pumping Bits Globally

  - Last Mile Bottleneck
    - Use twisted pair, cable, radio
  - Crowded City Bottleneck
    - Hard to install more wires
    - A lot of contention for wireless
    - Use microwave, radio
  - Trans-Oceanic Bottleneck
    - Use fiber, satellite

- Review: Where is the Physical Layer

  - Roughly, what happens which I click on a webpage?
    - Web request => turn click into HTTP request
    - Name resolution => check DNS for where the webpage is
    - Data transport => break message into packets/TCP segments
      - Should be delivered reliably and in-order
      - "And let me know when they got there" => retransmits if the request times out
    - Network layer => address each packet so it can traverse network and arrive at host
    - Network routing in IP => each router forwards destination
    - Data link scheduling (Ethernet) => break message into frames
      - Media Access Control (MAC)
      - "Can I send now? Can I send now?"
    - Physical layer

- Why Study Media?

  - Media affects protocol design
    - Low bandwidth led to tight encoding
      - Early phone lines, not needed for LANs
    - Broadcast LANs led to use of Multicast
      - Initialization and free copies, to IP multicast
    - Building wiring led to switching
      - Wiring closest to hubs to ATM 
    - Fiber led to rings
      - Point-to-point fibers lead to rings
    - Fiber led to Digital
      - Long haul telephone network becomes digital
    - Wireless leads to low bandwidths again
      - Laptops; need IPv6 compression on wireless links
  - We need to understand media tradeoffs when architecting networks
    - Think of flashlights vs. semaphores in the Morse Code analogy

- Twisted Pair Copper

  - Low bandwidth
  - Cheap, easy to install
  - Using twisted pair for higher rates today:
    - Standard twisted pair is limited by loading cables by telephone company to 4MHz
      - Shannon limit is around 56Kbps (not counting compression)
    - Two alternatives:
      - Better quality twisted pair cables for local area networks
        - e.g., Cat 3, Cat 5
      - Telephone company removes loading cables, reduces your length, and gives you ADSL
        - Asymmetrical

- Baseband Cable

  - e.g., Ethernet
  - High bandwidth (10-100MHz)
  - Hard to tap, expensive to install
  - Small distance (1-3km without repeaters)
  - Using coaxial cable today:
    - Coaxial cable has high bandwidth
      - Used for original 10Mbps Ethernet, but very clunky
      - Twisted pair used today
    - Cable still used in cable networks for cable TV and for data via cable modems
    - Divide bandwidth into 6MHz channels for each TV channel and one 6MHz channel for downstream data
    - Theoretically can reach 30Mbps but beware other users and bandwidth limits
      - Upstream much less

- Fiber Optics

  - Huge bandwidth (10 million MHz)
  - Can span continents with repeaters
  - Almost impossible to tap => point-to-point secure
  - Excellent electrical isolation
  - Thin and easy to install
  - Optics still expensive
  - Unidirectional
  - Modal Dispersion
    - The long path reaches the output slower
    - Can't send the next bit if the fast path of the next bit reaches the output before the slow path of the original bit
      - Inter-symbol interference
    - Solution: single mode fiber
  - Chromatic Dispersion
    - Different lights go at different speeds through glass
    - Spreads the signal out at output => can't send next bit until output width or you get ISI
    - Solution: use monochromatic light

- Wireless

  - Widely varying channel bandwidths/distances
  - Extremely vulnerable to noise and interference
  - Lower frequencies are omnidirectional, go through obstacles, and have lower speed
  - Higher frequencies are directional, get absorbed by obstacles, and have higher speed
  - Spectrum Allocation
    - Policy approach forces spectrum to be allocated like a fixed spatial resource
    - Reality is that spectrum is time and power shared
    - Measurements show that fixed allocations are poorly utilized
  - Wireless Data Options
    - 802.11: wireless LANs using a wireless access point (AP) at hotspot using unlicensed frequency band 2.4 to 4.485GHz (radio frequency)
      - 100m
      - Needs hotspot, but common and very cheap
      - AP configured with an SSID that you can see when doing "View Available Networks" and a channel number from 1 to 11
        - Non-overlapping channels (e.g., 1, 6, 11) can be used to triple bandwidth
      - Each AP periodically sends a beacon containing SSID
      - Each station scans all 11 channels looking for beacons to get list of networks
        - Some choice of AP and mobile sets up an association
      - Access protocol to send data is tricky because of hidden terminal problem
        - `A` and `B` can communicate with same output, but be unaware of one another, resulting in interference at the output
    - Bluetooth: ad hoc personal area networks with no AP
      - Master-slave
      - 4Mbps
    - WiMax: broader geographical range, smaller bandwidth of a few Mbps
    - 3G: cellular telephone networks carrying data at a few Mbps such as EVDO
      - Unlimited geographical range and true mobility
    - Microwave
      - Avoids right of way
      - May be cheaper than installing cable
      - Reasonable bandwidth
      - Has problems with rain
      - Up to 100km distance
    - Geosync Satellite
      - Avoides right of way
      - Good bandwidth
        - Limited from larger bandwidth due to limited sky space
      - Worldwide span
      - Large latency due to need to be geosynchronous
        - In order to be geosynchronous, the satellite must be far from Earth
      - Antenna cost: antenna need not be steerable due to the geosynchronous nature of satellites
      - Low Orbiting Satellites
        - Surround Earth with low-orbiting satellites
        - Perform handoffs between satellites instead of staying connected to same satellite
        - Requires a lot of satellites to be performant

- Media Pros and Cons

  - | Medium       | Speed             | Distance Span | Pros                           | Cons                          |
    | ------------ | ----------------- | ------------- | ------------------------------ | ----------------------------- |
    | Twisted Pair | 1Mbps-1Gbps       | 1-2km         | Cheap, easy to install         | Low distance                  |
    | Digital Coax | 10-100Mbps        | 1-2km         | Broadcast                      | Hard to install in a building |
    | Analog Coax  | 100-500Mbps       | 100km         | Cable companies use it now     | Expensive amplifiers          |
    | Fiber        | Terabits          | 100km         | Security, low noise, bandwidth | No broadcast, needs digging   |
    | Microwave    | 10-100Mbps        | 100km         | Bypass, no right of way need   | Fog outages                   |
    | Satellite    | 100-500Mbps       | Worldwide     | Cost independent of distance   | 250ms delay, antenna size     |
    | RF/Infrared  | 1-100Mbps/ <4Mbps | 1km/3m        | Wireless                       | Obstacles for infrared        |

- Problems in All Layers

  - Resource sharing
    - FDM/TDM/WDM
  - Addressing
    - TDM time slots
  - Synchronization
    - Clock recovery, spacing apart levels, transition
  - Interconnection
    - Physical layer repeaters are called hubs
    - Can have repeaters at each layer
      - Lower level repeaters are more robust and cheaper
      - Higher level repeaters are more knowledgeable about the payload



## Lecture 5: Framing

- Data Link Sublayers
  - Point-to-Point Links (2 nodes)
    - Bits => Framing => Error detection => Error recovery (optional) => Frames
  - Broadcast Links (≥2 notes)
    - Bits => Framing => Error detection => Media access => Multiplexing => Frames
    - Shared resources have to worry about collision, as there are multiple users across the same network
  - From a high-level view, the data link layer takes bits and provides frames
  - Quasi-reliable 1 hop frame pipe
    - If something is corrupted, it will be detected and trashed at the data link layer with extremely high probability
- Five Functions of Data Link
  - Framing: breaking up a stream of bits into units called frames so that we can add extra information like  destination addresses and checksums to frames (required)
    - First, as frames are required for error detection
  - Error detection: using extra redundant bits called checksums to detect whether any bit in the frame was received incorrectly (required)
  - Media access: there exist multiple senders, so we need traffic control to decide who sends next (required for broadcast links)
  - Multiplexing: allowing multiple clients to use data link; needs some info in the frame header to identify the client (optional)
  - Error recovery: go beyond error detection and take recovery action by retransmitting when frames are lost or corrupted (optional)
- Why Not Perform Error Recovery at Each Hop?
  - End-to-end argument
    - We need end-to-end or transport error recovery anyways
      - The only real guarantees are end-to-end => sender TCP to receiver TCP
      - Redundant, more overhead and buffering
    - Can't trust a series of hop-by-hop schemes because:
      - Crashes and other losses at intermediate nodes
      - Transport must work over both reliable and unreliable links
    - Used in old networking due to greater link unreliability
    - Thus, hop-by-hop is only a performance optimization
    - Extra cost (acknowledgement messages, buffering, etc.) not worth it when error rate is low
      - Worth it (quicker recovery, less wasted resources) when error rate is high and the latency of end-to-end recovery is unacceptable (within a compute cluster or storage area network)
- Why Framing?
  - Without framing, the bitstream is reserved for one sender and one client per sender
    - Need frames to add multiplexing information like destination addresses and destination client names
  - Frames offer a small manageable unit for error recovery and error detection
    - Add checksums to frames for error detection and sequence numbers, etc. for error recovery
- How Framing?
  - Flags and Bit Stuffing
    - Use special bit patterns or flags to delimit (i.e., mark boundaries) frames
    - Need bit stuffing to "encode" the user data to not contain the flags (e.g., HDLC)
  - Start Flags and Character Count
    - Use flags to indicate the start of data and a bit count to indicate end of frame
    - Bit stuffing not needed, but less robust (e.g., DDCMP)
  - Flags Supplied by Physical Layer
    - Use special physical layer symbols to delimit frames

- Fixed-Length Frames
  - Easy to manage for receiver
    - Well understood buffering requirements
  - Introduces inefficiencies for variable length payloads
    - May waste space (padding) for small payloads
    - Larger payloads need to be fragmented across many frames
    - Very common inside switches/routers
  - Requires explicit design tradeoff

- Length-Based Framing
  - Start | Length | Payload
  - To avoid overhead, we'd like variable-length frames
    - Each frame declares how long it is
    - e.g., DECNet DDCMP
  - What's the issue with an explicit length field?
    - Must correctly read the length field (bad if corrupted)
      - Need to decode while receiving
    - Still need to identify the beginning
- Sentinel-Based Framing
  - Allow for variable-length frames
  - Idea: mark start/end of frame with special "marker"
    - Byte pattern, bit pattern, signal pattern, etc.
    - But, we must make sure the pattern doesn't appear in the data
  - Two solutions:
    - Special non-data physical-layer symbol
      - Code efficiency (can't use symbol for data)?
    - Stuffing
      - Dynamically remove marker bit patterns from data stream
      - Receiver "unstuffs" data stream to reconstruct original data

- Stuffing Design by Sublayering
  - Frame => Stuffer => Add flags => Physical layer => Remove flags => Destuffer
  - Sublayering is a good design technique within layers as well
  - What happens if input data contains `01111110`? If the receiver gets `111110`?
- Byte Stuffing
  - Same as bit stuffing, except at byte (character) level
    - Generally have two different flags: STX and ETX
    - Found in DDCMP, BISYNC, etc.
  - Need to stuff if either appears in the payload
    - Prefix with another special character, CLE (data-link escape)
    - New problem: what if DLE appears in payload
  - Stuff DLE with DLE, like escape characters
    - Could be as bad as 50% efficient to send all DLEs
- The Engineering Solution
  - Ask the physical layer for more symbols that are never used in data
  - Easily possible in 4-5 encoding, as we have 16 data symbols, but 32 possible encoded values
  - Even after ruling out `00000` and `11111` we still have 14 unused symbols
  - Change interface to allow sending one of 16 data symbols (`0000` to `1111`) and special symbols for start of frame (SOF) and end of frame (EOF)
- Useful Principles
  - Each layer or sublayer exacts its penalty: e.g., clock recovery coding, framing bits
  - The end-to-end argument
  - Lower layers should not depend for correctness on assumptions about higher layers
  - All layers have some common problems to solve: e.g., synchronization, multiplexing
  - The best principles will/should be violated for pragmatic reasons
  - Layering and sublayering are a good way to understand and design new protocols



## Lecture 6: Error Detection

- Summary of Framing Techniques

  - Silence
    - Requires access to 3 levels
    - Ethernet
  - Special Pattern
    - If you are already using some encoding like 8-10, we can use an unused encoding
  - Bit Stuffing

- Big question: how can we add just 32 bits to a frame and detect almost any error with very high probability?

- Goal: Quasi-Reliability

  - The probability of a receiving data link passing up an incorrect frame to the client layer should be very, very small

    - Undetected error once in ~20 years
    - Needs to be so small because transport protocols do not insist on end-to-end checksums, a violation of the end-to-end argument

  - The probability of a receiving data link dropping frames sent by the sender should be small (once a day) to allow good performance

  - Add checksums to detect as large of a burst as possible, as many random (at least 3) errors as possible, and to detect any error pattern with a very high probability of:

    - $$
      1-\frac{1}{2^{32}}
      $$

- Types of Errors

  - Random errors: a noise spike or ISI makes you think a `0` is a `1` or a `1` is a `0`
  - Burst errors: a group of bits get corrupted because of synchronization or a connector is plugged in => correlated!
    - Modeling burst error: burst error of length `k` => distance from first to last is `k - 1`
      - Middle bits may or may not have been corrupted
  - Comparison:
    - Imagine a frame of size 1000 and an error rate of 1 in 1000
    - If random, all frames corrupted on average
    - If we get a burst of 1000 every 1000 frames, only 1 is lost

- Going Beyond Parity

  - Parity: XOR of bits
    - Can detect all odd bit errors in a frame
    - Can't detect 2 bit errors
  - Would like to do better than parity using so-called checksums for detecting larger number of errors (happens often) by adding more check bits (32 vs. 1)
    - Big picture: checksum as a hash => unlikely for the error to hash into the same value

- Basic Idea

  - If the receiver find s that `H' = Hash(M')`, then receiver passes `M'` up to the higher layer, otherwise it drops the frame
  - If `M` is not equal to `M'` and `H' = Hash(M')`, we have an undetected error
    - If errors are random and hash is also random in a 32-bit domain, then the probability of this occurring is only `1/2^32`

- Gentle Intro to Checksums

  - Telephone Exchange
    - Imagine you were sending a lot of numbers to a friend over a phone, and then end by sending the sum
    - Error detection: if the sum your friend receives is not the sum of the numbers she received, then there's an error
    - Undetected errors: an error that corrupts two numbers so that the sum works out
    - CRCs: instead of being based on addition, they're based on division
      - Also works using `mod 2`, but it's simplest to start with ordinary division

- Ordinary Division Checksum

  - Consider message `M` and generator `G` to be binary integers

  - Let `r` be the number of bits in `G`

  - We find the remainder `t` or `2^rM` when divided by `G`

    - Why not just `M`? So we can separate the checksum from the message at the receiver by looking at the last `r` bits

  - Thus:

    - $$
      2^rM=kG+t\\
      2^rM+G-t=(k+1)G
      $$

    - So we add a checksum `c = G - t` to the shifted message and the result should divide `G`

  - Has reasonable properties, however, integer division is hard to implement

    - Prefer to do without carries

- The Big Idea

  - In ordinary division checksums, we transmitted a message plus a checksum that was divisible by the generator `G`
    - Thus any errors that cause the resulting number to not be divisible by `G` (invalid codewords) will be detected
  - In CRCs, we do the same thing, except we use `mod 2` arithmetic instead of ordinary arithmetic
  - `mod 2` arithmetic: addition and subtraction are XORs so there is no carry
    - Can implement at high speeds

- Modulo 2 Arithmetic

  - No carries: repeated addition does not result in multiplication

  - Multiplication is normal is normal except for no carries

    - Shift and XOR instead of shift and add

  - Similar algorithm to ordinary division

    - Again, let `r` be the number of bits in `G`
    - We find the remainder `c` of `2^r-1 M` when divided by `G`

  - Thus, `2^r-1M = kG + c`, thus:

    - $$
      2^{r-1}M-c=kG\\
      2^{r-1}M+c=kG
      $$

    - Send `c` as checksum

  - How `mod 2` Division Works

    - For CRC, we need to repeatedly add `mod 2` multiples of the generator until we get a number that is `r - 1` bits long that is the remainder

    - The only way to reduce number of bits in `mod 2` arithmetic is to remove the MSB by adding `mod 2` a number with a `1` in the same position

    - ```pseudocode
      While no more bits:
      	If MSB = 1, XOR with generator
      	Shift out MSB and shift in next bit
      ```

- Implementing CRCs

  - The current remainder is held in a register initialized with the first `r` bits of the message
  - If the MSB of the current remainder is `1`, then XOR the current remainder with the divisor; if the MSB is `0`, then do nothing
  - Shift the current remainder 1 bit to the left and shift in the next message bit
  - Faster to shift more bits at a time using a table of precomputed checksums

- CRC: Polynomial View

  - `101` and `011` can be represented as `X^2 + 1` and `X + 1`

    - `X^i` term iff the `i`th bit is `1`

  - Normal addition: `X^2 + X + 2`

    - No carries between powers
    - `+2` is bad: fix by using `mod 2` addition to get `X^2 + X`
      - Applies to `X` terms as well

  - Can think of CRC computation as dividing  a shifted message polynomial (multiplied by `x^r-1`) by CRC divisor polynomial and adding remainder

  - Equivalent to arithmetic view, but polynomial is easier to analyze

  - Errors in Polynomial View

    - We model bit errors in positions `i`, `j`, `k`, etc. as the channel adding an error polynomial:

      - $$
        X^i+X^j+X^k+\cdots
        $$

    - Since the message polynomial divides the generator, the error will not be detected iff the error polynomial divides the generator

      - Or in other words if one cannot multiply the generator by another polynomial to get the error polynomial

  - Properties:

    - CRC-16:

      - $$
        X^{16}+X^{15}+X^2+1
        $$

      - Error results in adding in a polynomial => use normal polynomial multiplication intuition

    - Single-bit errors: result in addition of `X^i`

      - If `G(x)` has at least two terms, any multiple of `G(x)` will have two terms

    - Two-bit errors correspond to adding `X^i + X^j`



## Lecture 7: Error Recovery

- Error Detection

  - If the error polynomial divides the generator, we have a problem => undetected error

    - $$
      \frac{M(x)+E(x)}{G(x)}=\frac{M(x)}{G(x)}+\frac{E(x)}{G(x)}
      $$

  - CRCs want to detect:

    - All 1-bit errors

      - As long as the generator has 2 terms, there is no way a single-term error polynomial can be generated

    - All 2-bit errors

    - All odd-bit errors

    - All bursts of size degree of CRC

    - Every kind of error with probability:

      - $$
        1-\frac{1}{2^d}
        $$

  - Implementing CRCs

    - The current remainder is held in a register initialized with the first `r` bits of the message
    - If MSB of current remainder is `1`, then XOR the current remainder with divisor, if the MSB is `0`, do nothing
    - Shift the current remainder `1` bit to the left and shift in next message bit
    - Faster to shift, say, 8 bits at a time (your assignment) using a table of 256 precomputed checksums of all possible 8-bit checksums

  - CRC in Hardware

    - Registers `R0` through `R4` are several single-bit registers corresponding to the single multi-bit register
    - XOR placed to the right of register `i` if bit `i` is set in the register
    - When a message bit shits in, all registers send (in parallel) their bit values to the left, some through XOR gates
      - Combines left shift of an iteration with MSB check and XOR of next iteration
      - XOR during left shift
    - Avoids check for MSB: output of `R4` as input to all XORs
    - In practice, to implement at terabits, we need to shift multiple bits (say 8) per clock cycle using table lookup

  - Back to the Big Picture

    - How can we add just 32 bits and catch all errors with high probability?

  - Hamming Distance

    - Recall, we used CRCs to do better than parity using so-called checksums for detecting a larger number of errors (happens often)
      - An idea called Hamming distance explains why some codes detect and correct more bits
    - Hamming distance between two strings `S` and `R` is the number of bit positions at which they differ

  - Error Detection as Coding

    - Computation view: add bits to the end of a frame for detecting errors
      - Parity adds 1, CRC adds 32
    - Coding view: we take every packet `P` and encode it as a frame `F = C(P)` in any way you wish
      - One way is to add a checksum but there are other examples
      - After coding, some codewords are valid and some are invalid
      - Allows us to abstract across details of code and use Hamming distance
    - Triple code: imagine we encode every bit in `P` as 3 identical bits in `F`

  - CRCs and Hamming Distance

    - While CRCs are really chosen for burst detection, then Hamming distances are also important
    - CRC-32 layers have a Hamming distance of 5 for frame sizes less than 360B and 4 for larger frames
      - CRC-32 is used in 802.11, Ethernet, SATA, etc.
      - This implies that CRC-32 can detect 4 random bit errors for most frames
        - Actually 5 because of odd-bit guarantee
    - There is a special 32-bit polynomial called CRC32K by Koopman that has Hamming distance of 6 fairly large frame sizes

  - Hamming Distance, Detection, and Correction

    - Can detect `d` random bit errors if Hamming distance is `d + 1`, because flipping `d` bits cannot move from valid codeword to another
    - Can correct `d` errors if Hamming distance is `2d + 1`
      - Assign invalid codewords to closest codeword

- Error Recovery

  - Why Error Recovery at Data Link?

    - Used later: protocols like TCP use the same ideas
    - Still used at data link: some existing protocols like HDLC and Fiber still do error recovery at data link
    - Non-trivial protocol: our first example of the problems caused by varying message delay and errors (frame loss, crashes)
    - Technology seesaw: hop-by-hop becoming popular again to reduce latency

  - Correctness Specification

    - Packets given to the sending data link must be delivered to the receiver without duplication, loss, or mis-ordering

  - Assumptions

    - Assumes error detection: assumes undetected error rate small enough to be ignored
    - Loss as well as errors: whole frames can be lost in a way not detected by error detection
    - FIFO: physical layer is FIFO
    - Arbitrary delay: delay on links is arbitrary and can vary from frame to frame

  - Motivations for Stop and Wait Protocol

    - Loss: first packet drops and second arrives
      - Must retransmit
    - Duplication: packet is received, but sender resends before `ack` arrives
      - Must defend against early retransmits
    - Livelock: cannot throw away duplicates, as the data might have duplicates
      - Need sequence numbers
      - If the `ack` fails, then the receiver is expecting the next sequence number, but the sender is stuck resending the first packet
        - Must `ack` even duplicates
    - Loss: receiver sent an `ack` for a a previous packet but was interpreted by a sender as an `ack` for a later packet
      - Must number `ack`s

  - Going Deeper

    - Correctness: how do we show it works in all cases (infinite sequence of executions)? => invariants
    - Sequence number: do we need an infinite number of bits? => no
    - Performance: send only one at a time, bad over satellites, can do better => sliding window
    - Initialization: how do we get started and synchronize sequence numbers in the face of crashes?

  - Naive Code for Stop and Wait

    - Sender code:

      - ```pseudocode
        Sender keeps state variable SN, initially 0, and repeats the following loop
        
        Loop forever:
        	Accept a new packet from higher layer and store it in buffer B
        	Transmit a frame (SN, B)
        	If (ACK, R) frame received and R != SN, then
          	SN = R
        		Go to beginning of loop
        	Else if the previous condition does not occur after T sec
        		Re-transmit
        ```

    - Receiver code:

      - ```pseudocode
        Receiver keeps state variable RN, initially 0
        
        When an error-free data frame (S, D) is received:
        	On receipt:
        		If S = RN then:
        			Pass D to higher layer
        			RN = RN + 1
        			Deliver data m to client
        			Send (ACK, RN)
        ```

  - Correct Code for Stop and Wait

    - Sender code:

      - ```pseudocode
        Sender keeps state variable SN, initially 0, and repeats the following loop
        
        Loop forever:
        	Accept a new packet from higher layer and store it in buffer B
        	Transmit a frame (SN, B)
        	If (ACK, R) frame received and R != SN, then
          	SN = R
        		Go to beginning of loop
        	Else if the previous condition does not occur after T sec
        		Re-transmit
        ```

    - Receiver code:

      - ```pseudocode
        Receiver keeps state variable RN, initially 0
        
        When an error-free data frame (S, D) is received:
        	On receipt:
        		If S = RN then:
        			Pass D to higher layer
        			RN = RN + 1
        			Deliver data m to client
        		Send (ACK, RN) // Ack needs to be unconditional
        ```

  - Correctness Observations

    - When sender first gets to `N`, no frames with `N` or `ack`s with `N + 1` and receiver is at `N`
    - When receiver first receives frame `N`, entire system only contains number `N` => only two numbers in system

  - Band Invariant

    - Two bands of equal values `y = x` or `x = y + 1`
    - Prove invariant by checking a small number of state transitions
      - 6 cases: retransmission, error, reception, receive `ack`, send `ack`, and send new frame
      - Just need to show that invariant is preserved by these 6 protocol actions/state transitions



## Lecture 8: Performance Measures and Sliding Window Protocols

- Error Recovery

  - State View
    - States of sender, receiver, and links at various points in the space-time diagram
  -  So far, we've shown:
    - Correctness: based on band invariant
    - Sequence number: one bit suffices
    - Performance: send only one at a time
      - Bad over satellites or any link where the bandwidth-delay product is large
    - Initialization: coming up after performance

- General Performance Measures

  - Throughput: jobs completed per second
    - System owners want to maximize this
  - Latency: worst-case time to complete a job
    - System owners want to minimize this

- Network Specific Measures

  - 1-way propagation delay: time for transmitted bit to reach receiver
    - Contrast to transmission rate (rate at which sender is sending)
  - Pipe size: `Transmission Time * Round-Trip Propagation Delay`
    - Need to pipeline if pipe size is large
    - Sometimes called the bandwidth-delay product

- Sliding Window Protocols

  - Needed to use more of a link's capacity when its pipe size is large

  - Definitions

    - Window: sender can send a *window* of outstanding frames before getting any `ack`s
      - Lower window edge `L` can send up to `L + w - 1`
    - Receiver numbers: receiver has a received sequence number `R`, which is the next number it expects
      - `L` and `R` are initially `0`
    - Sender code: retransmits all frames in current window until it gets an `ack`
      - `ack` numbered `r` implicitly acknowledges all numbers `< r`
    - Two variants: receiver accepts frames in order only (go-back-`N`) or buffers out-of-order frames (selective reject)
      - Selective reject sends back an `ack` with a list of out-of-order packets

  - Code

    - Go-Back-`N`

      - Sender code:

        - ```
          Sender keeps state variable L, initially 0
          
          Send (s, m) // Send data message m with number s
          	The sender can send this frame if:
          		m corresponds to s-th data item given to sender by client AND
          		L ≤ s ≤ L + w - 1 // In allowed send window
          		
          Receive (r, Ack) // receive an ack number r
          	On receipt:
          		L := r // Slide lower window edge to ack number
          ```

      - Receiver code:

        - ```
          Receiver keeps state variable R, initially 0
          
          Receive (s, m) // Receive data message m with number s
          	On receipt:
          		If s = R then:
          			R := s + 1
          			Deliver data m to client
          
          Send (r, Ack) // Send ack with number r
          	// Receivers typically send acks in response to data
          	// 	messages, but our code can send acks anytime
          	r must equal R
          ```

    - Selective Reject

      - Sender code:

        - ```
          Sender keeps a lower window edge L initially 0 but also an array  with a bit set for all numbers acked so far. Initially, all bits are clear. In practice, we implement this array by a bitmap of size w which we shift.
          
          Send (s, m) // Send data message m with number s
          	The sender can send this frame if:
          		m corresponds to s-th data item given to sender by client AND
          		L ≤ s ≤ L + w - 1 AND
          		s has not been acked // New for selective reject
          		
          Receive (r, List Ack) // Receive an ack number r with List of 														//		received numbers > r
          	On receipt:
          		L := r // slide lower window edge to ack number, mark numbers
          						// in List as acked at sender
          ```

      - Receiver code:

        - ```
          Receiver keeps a receiver number R initially 0, but also an array with a bit set for all numbers received so far. Initially all bits are clear. In practice, we implement this array again by a bitmap of size w which we shift. In addition to the bit map, we have a buffer for each number where we can store out of order messages.
          
          Receive (s, m) // Receive data message m with number s
          	On receipt:
          		If s ≥ R then:
          			Mark s as acked and buffer m
          			While R acked do:
          				Deliver data message at position R
          				R := R + 1
          				
          Send (r, List Ack) // Send ack with number r and List of received
          										// 		received numbers > r
          	r must equal R
          	List contains received numbers > R
          ```

  - Implementation and Other Details

    - Timers: works regardless of values, but needed for performance
      - So caclulate round-trip delay
      - Need only one timer (for lowest outstanding number) in go-back-`n`
      - Need one for each window element in selective reject
    - In selective reject, have to send an `ack` with `R` and a bitmap of numbers greater than `R` that have been received
    - Piggybacking: to reduce frames sent

  - How Big Should the Sequence Number Space Be?

    - Alternating bit: modulus is 2 (just one bit)
    - Go back `w`: need a modulus of `w + 1`
    - Selective reject: need a modulus of `2w`

  - Flow Control

    - Windows provide static flow control
      - Can provide dynamic flow control if receiver `ack`s indicate what receiver will buffer
    - Flow control without error recovery
      - Credits
      - Rate control (sender does not send > `R` frames/sec)

- Initializing Link Protocols

  - Naive Restarts
    - Send a restart message => wait for `ack` to initialize sender and receiver
    - Can be fooled by prior restarts
  - How to design a reliable initialization protocol
    - Non memory after crash: can do correctly if sender keeps even one bit that can survive a crash
    - Determinism: can send restart messages with random numbers and only send data when numbers are `ack`ed
      - High probability only
    - Message lifetimes: if no message can live on a link for more than `T` seconds, simply wait `T` seconds after a crash for all old messages to die out



## Lecture 9: Local Area Networks and Ethernet

- Big Transition in this Class

  - From 1 sender, 1 receiver to many senders, many receivers
  - New problem: how to share a link (MAC)
  - Inherently sequential
  - Link shared among multiple senders, also known as:
    - Multiaccess links: there are multiple nodes that may simultaneously access the link
    - Broadcast links: every transmission  can be heard by all other stations
    - Local area networks (LANs): the geographical area serviced by a LAN is local and small
      - Typically 1-10km

- Why LANs

  - Cost: connect up all computers in a local area, saves wiring costs to share one wire
  - Bandwidth: provides high bandwidth and low error rates for local group of users
    - Worth it because most high-bandwidth distributed computing has access locality

  - Statistical multiplexing: time division multiplexing is not a good idea when user traffic is as bursty as data is, as fixed bandwidths are wasteful
    - Bursty = high peak/average ratio
    - Each user gets access to entire LAN bandwidth when other users are idle
    - As more users are added, they share the bandwidth
    - Better throughput and latency in the average case => what Ethernet does

- Statistical vs. Strict Multiplexing

  - Strict multiplexing: TDM or FDM where a user is given a fixed allocation regardless of whether the user has data to send or not
  - Bursty: traffic has a high peak/average ratio
  - Analysis: gives each user `B/N`, where `N` is the number of possible sources
    - Statistical multiplexing attempts to give each user `B/x`, where `x` is the number of busy users
    - `N` is large (100-1000), while `x` is small (1-10)

  - Example:
    - Suppose 100 users each transfer a 125KB file every 2 hours
    - At 10Mbps, a 125KB file takes 0.1 seconds to transmit (statistical multiplexing)
    - At 0.1 Mbps, file takes 10 seconds to transfer (strict multiplexing)

- Aloha

  - Ethernet predecessor: multiple ground stations in various parts of Hawaii
  - Problem: couldn't detect collisions or sense when channel was busy, similar problems in 802.11
  - Slotted Aloha: reduces vulnerable period by half, but requires a common clock

- In-Transmission Collision Detection and Semi-Reliability

  - Metcalfe knew about Aloha and new he could do better because of the smaller distance
  - 1500B frame involved in a collision
    - Ethernet aborts transmission after 64B
    - Aloha will send the entire 1500B and detect the collision when `ack` is not received
    - Better for large frames and large frame sizes improve efficiency

  - No recovery from frame corruption (1 in a million)
    - However, collisions are infrequent
    - Semi-reliable: detect collisions and retransmit in hardware

- What is a Collision?

  - The notion of a collision is nuanced

  - Definition: a station `A` detects a collision if two or more signals from different senders coexist at `A`

  - Like relativity: different stations detect collisions at different times

    - Worse, without care, some stations may detect collisions and some may not

  - Need mechanisms: want to convert relativity to universality, so that if receiver detects a collision, so does the sender, so sender can retransmit

    - One big mechanism is forcing a minimum packet size
    - If a long enough packet is sent, then the sender can detect the collision, causing a retransmission

  - Waves, not balls: on Ethernet and 802.11, frames are sent as waves that pass through each other and don't collide and rebound like balls

  - Answers:

    - The min packet size is the pipe size

      - $$
        \text{Round trip delay}\times\text{Transmission speed}
        $$

    - Ethernet does binary exponential backoff

      - After attempt `I`, each station randomly picks a random number of slots between `0` and `2^I - 1`
      - A slot is 51.2 µsec

    - Both ideas are now classic

- Ethernet

  - Three main mechanisms:
    - Carrier sense and deference: no point transmitting when someone else is speaking
    - Collision detection: stop frame (< 1500B) when before 64B, you detect a collision
    - Exponential backoff: collisions very frequent, so must retransmit
      - Random backoff avoids synchronized collisions
      - Dynamically adjust to number of colliders

  - Smaller mechanisms to make main ideas work:
    - Slot time = `2T`, where `T` is 1-way propagation delay limited to 51.2 µsec = 64 bit times at 10Mbps: maximum delay to detect a collision
    - Minimum packet size: 64B to avoid finishing transmission before collision is detected
      - Pad if needed

    - Jam: transmit small number of bits after you detect a collision to ensure that other transmitters also detect collision
    - Collision detection: one way is to use Manchester with average DC level per bit
      - Collision detection by detecting increased voltage level
      - Better ways today

  - Implementation Details
    - Limited distance (2.5km)
      - 500m wires, 4 repeaters

    - Thin wire, thick wire
    - Repeaters/hubs: important device, reads in a bit and writes out a bit on other side, boosting signal strength
    - Physical topology is a star or trees




## Lecture 10: 802.11 and Bridging

- Ethernet (cont.)

  - Cost of Statistical Multiplexing in Ethernet
    - If distance goes up by a factor of 10 or speed, then what happens to minimum packet size?
      - Why is it wasteful?

    - 100 Mbps Ethernet proposal only has 200m extent
    - Gigabit Ethernet? Span too small
      - Instead replace shared wire with point-to-point links and hubs with switches

    - The cost of statistical multiplexing is why Ethernet is limited to LANs

  - From CSMA/CD to Switching
    - If `A` talks to `R` at same time as `B` talks to `S`, there is a collision
    - `A` can talk to `R` at the same time as `B` talks to `S` with no collision
      - Switch buffers and allows parallel connections

    - Gigabit Ethernet no longer uses CSMA/CD
      - We study it because similar Media Access protocols are used, especially in wireless and 802.11

- 802.11

  - WLAN: IEEE 802.11b
    - Data rate:
      - 1, 2, 5.5, 11 Mbit/s
      - User data rate maximum is approximately 6 Mbit/s

    - Transmission range:
      - 300m outdoor, 30m indoor
      - Maximum dat rate is ~10m indoor

    - Frequency
      - Free 2.4GHz ISM-band

  - Physical Channels
    - 12 channels available for use in the US
      - Each channel is 22MHz wide
      - Only 3 orthogonal channels
      - Using any others causes interference

  - Carrier Sense Multiple Access
    - CSMA: listen before transmit
    - If channel sensed idle: transmit entire packet
    - If channel sensed busy: defer transmission
      - Persistent CSMA: retry immediately with probability `p` when channel becomes idle (may cause instability)
      - Non-persistent CSMA: retry after random interval

  - Hidden Terminal Problem
    - `B` can communicate with both `A` and `C`
    - `A` and `C` cannot hear each other – not a single shared channel
    - Problem:
      - When `A` transmits to `B`, `C` cannot detect the transmission using the carrier sense mechanism
      - If `C` transmits, collision will occur at node `B`

    - Solution:
      - Hidden sender `C` needs to defer

  - RTS/CTS (MACA)
    - When `A` wants to send a packet to `B`, `A` first sends a Request-to-Send (RTS) to `B`
    - On receiving the RTS, `B` responds by sending Clear-to-Send (CRS), provided that `A` is able to receive the packet
    - When `C` overhears a CTS, it keeps quiet for the duration of the transfer
      - Transfer duration is included in both RTS and CTS

  - Backoff Interval
    - Problem: with many contending nodes, RTS packets will frequently collide
    - Solution: when transmitting a packet, choose a backoff interval in the range `[0, CW]`
      - `CW` is contention window
      - Wait the length of the interval when medium is idle
        - Countdown is suspended if medium becomes busy
        - Transmit when backoff interval reaches 0

      - Need to adjust `CW` as contention varies
        - Similar in spirit to Ethernet backoff

  - Concepts/Conclusions
    - Statistical multiplexing is a big idea
    - Important of pipe size or bandwidth delay product in determining efficiency
    - Logical vs. physical topology
      - 10M Ethernet is logically a bus, but physically a star

    - Ethernet ideas mostly gone in Gigabit Ethernet, but some ideas like CSMA live on in 802.11
      - Also, 10-100 Mbps Ethernet is still used

- Bridging

  - Overview

    - Review of what Gigabit Ethernet is and 802.11
    - Understand the structure of Ethernet addresses (still used today when you have a MAC address)
    - Then, move on to how to interconnect Ethernets at the data link level (same as switches in Gigabit Ethernet)
      - Not a router, something in between

  - Multicasting

    - One sender sending to multiple receivers
      - Generalizes broadcasting (sending to all) by sending to a subset of stations

    - Useful for auto-configuration
    - 3 examples:
      - Solicitation: clients multicast to any server
      - Advertisement: servers multicast to any client
      - Free copies: servers multicast to all clients

    - If the most significant bit of the address is a `1`, then it is a multicast address

  - Multicast Addresses

    - 6-byte Ethernet addresses assigned by 802 committee
      - Vendors buy a fixed 3-byte code
      - They can then assign the remaining 3 bytes (for destination addresses) or 2 bytes (for 5-byte type fields)
      - Can buy more codes

    - Multicast address denoted by MSB
      - Get 2^24 multicast and unicast addresses and 2^16 types/block

    - Common multicast addresses (i.e., all IP end-nodes, all IP routers) and type fields are standardized
    - Broadcast address is all `1`s
      - Multicast is better
      - Ethernet hardware should only pass up to software packets with DA = my address or a multicast that station listens to
      - Hashing or CAMs

  - Local Area Networks Review

    - Till last lecture, all the physical links we studied were a single wire with one sender and one receiver
      - A local area network (LAN) is like a shared wire with multiple senders and multiple receivers

    - Common LANs are Ethernet and token ring
      - In Ethernet, stations transmit when they want to; if two or more transmit at the same time, there is a collision and they retransmit
      - Token rings when station has token

    - Ethernets were successful but had limitations
      - Hence the need for bridging to "extend" LANs

    - Bridges are different from hubs (they are more akin to switches) because they are data link relays, they store and buffer frames and relay frames, not bits
      - First, a small detour into "multicasting"

  - Bridging: An Exercise in Invention

    - Problem Statement

      - c. 1980 at Digital: Ethernets under attack
      - Ethernet had limited distance (2.5km) and stations (8,000)
        - Also, perception that Ethernet collapsed at high loads
        - Token ring emerging

      - Question: how can we extend 2 Ethernets to make a larger Ethernet that has twice the distance, twice the bandwidth, and twice the number of stations?
      - Repeaters don't work, as they repeat all bits everywhere
        - So bandwidth will not be doubled
        - Routers work, but are expensive because we need different routers for each high-level routing protocol on the Ethernet
          - Make it work without looking at the routing header

      - How can we extend LANs *transparently*: without end-stations knowing that they are on an extended LAN?

    - Initial Solution

      - Receive frame with destination and source headers
      - If the received frame's destination is on the same interface, we drop it
        - Otherwise we forward it on the destination's interface

    - Refinements for Efficiency and Correctness

      - Database could be built manually => error prones
      - Learn based on source address and forward based on destination address and send to other interface when no info is known (flooding)

    - Generalizations

      - Any LAN or data link that puts both sources and destination addresses in frames (includes all 802 LANs)
      - Any topology without cycles
      - More than two bridge ports

    - Code

      - ```
        Receive frame F on interface X
        AddTable(F.Source) // Learn source, refresh timer
        Y = Lookup(F.Dest) // Lookup destination
        If (Y = NIL) then // Unknown destination
        	Forward frame F on all interfaces Y != X // Flood
        Else if (Y != X) then
        	Forward frame F on interface Y
        Else if (Y == X) // Filtering
        	Drop frame F
        
        TimerExpiry(E) // Timer for entry E fires
        E.interface = NIL // Re-enable flooding
        ```
  
  - Bridge Terminology and Summary
    - Transparency, promiscuous receive, flooding, filtering
    - Main idea: learn based on source addresses and forward based on destination addresses
      - Use flooding when there is no info, and timeout to handle stale learning information
  
  - Realization
    - Need much higher performance than router, which handles all frames addressed to it
    - Need to decide whether to drop or forward frames in minimum inter-frame time on Ethernet, 51.2us on each port
      - Otherwise, could drop some frames that need to be forwarded while examining others that have to be filtered
    - First DEC implementation by Mark Kempf in 1984 technology
      - Achieved forwarding in minimum frame time with low cost




## Lecture 11: Spanning Tree and Routing vs. Bridging

- Bridging

  - Avoiding Cycles

    - Cycles are useful for the purposes of redundancy
    - Designate a root bridge based on a shortest path

  - Centralized Algorithm

    - Root is minimum ID nodes
    - Other bridges find the minimum port, the port through which it has the shortest path to root (parent link)
    - Each bridge also finds the ports for which this bridge is on the shortest path between root and corresponding LAN: designated ports
    - Each bridge turns on the minimum port and all designated ports
      - On/off are software states
      - Always receive hello and management messages on all ports
      - Drop data packets to/from off ports
    - To be atree, each LAN must have a unique path to every other LAN
    - Algorithm guarantees that each LAN can get to the root only through the designated bridge for the LAN
      - Designated bridges have a unique path through their parent LAN

  - Distributed Algorithm

    - All nodes send a hello message saying their ID and current estimates to root `(ID, r, d)`

      - Every node `N` keeps an estimate `r(N)` and `d(N)` of its current estimate of root and distance

    - On hearing a smaller root, adopt that root and update your distance as `d + 1`:

      - ```
        On receipt of (r, d) at node N:
        	If (r < r(N)) then:
        		r(N) = r
        		d(N) = d + 1
        	Else if (r = r(N) and d < d(N)) then:
        		d(N) = d + 1
        ```

    - Bridges must wait some time after the estimates stabilize to turn on ports and start forwarding to avoid loops

  - Conclusion

    - Necessity is the mother of invention
    - Find new problems that matter and find creative solutions
      - Challenge the dogma
    - The big ideas: auto-configuration, filtering, flooding, wire speed forwarding, spanning tree, designated bridges
    - Link layer relays versus physical layer relays
      - Next: routing layer relays, aka Internet routers

- Bridges vs. Routers

  - Bridges only see MAC addresses, not routers
  - Bridges are short-circuited from the router's point of view
  - Routers maintain an ARP table (populated by a demand-driven protocol) to map MAC addresses
  - Basic Question
    - Original data link was single hop, but bridges make things multi-hop
    - So why have routers?
      - Main reason is that data link headers were developed before bridges, so there's no support for data link relays in the data link header
      - The opposite is true for routing headers
  - Why Bridges are Bad
    - Address incompatibility
    - Max packet size incompatibility
    - Bandwidth incompatibility
    - Large networks
      - 802 address is flat, routing addresses are hierarchical
        - Bridges have to learn all addresses in an extended LAN (more memory)
        - Routers only learn addresses within each level of their hierarchy
      - Spanning tree is inefficient
        - Does not route packet on shortest path between two points
        - Increased latency and smaller throughput
        - Flooding wastes throughput
  - Why Hierarchical Addresses?
    - If we used bridges to connect the global Internet, each bridge would store billions of MAC addresses
    - MAC addresses are flat and unique worldwide, but IP addresses are hierarchical
    - Scalability requires hierarchy
  - Why Bridges are Good
    - Generality: bridges allow stations with different routing protocols to use the same extended LAN
    - Cost-performance: since they do less, bridges cost less than routers with the same performance
    - Control traffic: smaller amount of routing control traffic (spanning tree is small by comparison)
  - Conclusion
    - Each has a place
    - Bridges can be used to connect a small number of compatible LANs to form an extended LAN
    - Routers connect extended LANs to form a routing network
    - Most routers today are multi-port devices, where some ports can be bridges and some can be routers



## Lecture 12: IP Addressing and Overview

- Topology
  - Terminology: ISPs, POPs, autonomous systems, NAPs, peering
    - Autonomous systems: very much synonymous with domains
      - The whole philosophy of the Internet is ordered chaos => everyone should be able to do their own things *while following certain rules*
    - NAP (Network Access Point): commercial vendors must come together at a point called a NAP
      - NAPs are very congested placed, so most people today use peering
    - Peering: commercial networks build a line between their networks
      - Ex) MCI tells Sprint that they will carry their customers for free if they do the sames
      - Encourages the interconnectedness represented by the Internet

- Basic Internetworking in IP
  - Goal from start: unlike DECNET, SNA, etc. starts with a hierarchy of physical networks with network specific routing that IP doesn't care about, to create an Internetwork of physical networks
  - IP's role: to route packets to the right physical network based on the network number
    - Not to forward within a network, but to forward between networks
      - Allow different networks to talk to each other
    - Offers a so-called datagram service with possible fragmentation and reassembly to deal with different maximum packet sizes
      - Datagram service: send things, if they get there, then great
    - Realized that IP routers would have to fragment messages if necessary
      - Different networks had different limits
  - Error messages: companion protocol called ICMP for error messages (header checksum failed, maximum time exceeded, redirect, etc.)

- IP Evolution

  - ARPANET started by linking government and university sites in the 70s
  - NSFNet in 1983: ARPANET splits up into MILNET and ARPANET
    - In 1984, NSF establishes NSFNet to be backbone
    - Campuses attached to backbone via regional networks
    - Strict hierarchy breaks down because of direct connections between providers

  - Multiple providers by the late 80s: Internet becomes worldwide
    - From a research network to production quality
    - Multiple autonomous providers that need to work together

- Names and Address

  - Names: when you send to a domain name, a resolver in your host translate the name to a 32-bit IP address
    - All messages carry UP destination addresses

  - Domain Name Service (DNS): the translation is done using using the DNS

- Original IP Addresses: Classful

  - Original model: small number of large networks (class A), moderate number of campus networks, large number of LANs
  - Idea: hierarchical address with a moveable boundary
    - Analogous to phone area codes, which give multiple area codes to larger areas

  - Classes:
    - Class A: starts with a `0`, 1 byte reserved for the net, and 3 bytes reserved for the host
    - Class A: starts with a `10`, 2 byte reserved for the net, and 2 bytes reserved for the host
    - Class A: starts with a `110`, 3 byte reserved for the net, and 1 bytes reserved for the host

- Old IP Forwarding

  - Find destination: extract network number of destination address by parsing and checking out for class A, class B, etc.
  - Find hop reached?: if the network number of destination is equal to the network number of one of this router's local interfaces, deliver the packet
    - Map to local address using ARP or some such network specific protocol

  - Lookup router table: lookup network number in the corresponding routing table
    - If it exists, deliver packet to corresponding next hop
    - If no route entry exists, send to default router
      - Looks silly, but is a great way to avoid keeping lots of table entries in stub organizations like UCLA

- Challenge-Response

  - One level of hierarchy is good, but IP quickly ran into two scaling challenges
    - Inefficient address usage: any organization that needed more than 255 addresses asked for a class B address (64,000) and they quickly ran out
    - Routing table growth: the response to no more class B addresses was to assign multiple class C addresses
      - But now, every backbone router needed to know more addresses, more routing traffic, search times, etc.

  - Response: changed IP forwarding to longest matching prefix
    - Why?

- Subnetting and Supernetting

  - Supernetting: done recursively, leads to backbone routers only having hundreds of thousands of prefixes of lengths 8-32
    - Longest matching prefix matching helps routers scale => we want longest matching because it's deeper down in the hierarchy
    - Problem is even worse today

  - Temporary measures: often today, new organizations are given 1 IP address and use NAT (use of TCP port numbers to extend the range of an organization's address)
    - Need the move to IPv6 (128 bits)

- IP Evolved to Meet Challenges

  - Challenge 1: interconnecting diverse networks => net numbers (Class A, 1 byte)
  - Challenge 2: Ethernets led to an explosion of networks => hack to add Class B/C
  - Challenge 3: Class B addresses ran out => give consecutive class Cs and use longest prefix match
  - Challenge 4: even class Cs started running out => NAT and concurrent move to IPv6

- New IP Forwarding

  - Lookup: find longest matching prefix `P` of destination IP address in packet of forwarding table
  - Default or local?: if `P` is `NIL`, forward on default route
    - If the next hop associated with `P` is a local interface, deliver packet
    - Map to local address using ARP or some such network specific protocol

  - Send on its way: if not, send packet to next hop route associated with `P`
  - Backbone routers in default-free zones have to have many hundred thousand prefixes to reach everyone
    - Enterprise routers have 1,000s because of heavy use of default routes

- Four Problems Endnodes Must Solve

  - Problem 1: Routers need data link addresses of endnodes
  - Problem 2: Endnodes need DL address of 1 router
  - Problem 3: Endnodes on the same LAN should be able to communicate without a router
  - Problem 4: Endnodes should go through as direct a path as possible

- IP Solutions to Endnode Problems

  - Problem 1: ARP for MAC address of destination
  - Problem 2: a service called DHCP gives you the IP address of one router (autoconfiguration)
    - DHCP protocol has a well-known multicast address
    - Routers are configured by a manager for DHCP

  - Problem 3: two endnodes know they are on the same subnet by comparing masks, then ARP
  - Problem 4: send to router and router sends redirect if packet returns on interface it entered router
    - Ignore this code in project

- IP Forwarding: Overview

  - Need to understand how to forward packets using longest matching prefix (linear search is fine)
  - Need to understand how to implement ARP in your router
  - Need to understnad how to implement ACLs using simple linear search
  - To implement all this and ACLs, you need to understand all the fields in an IP packet, including the TCP header

- Basic Packet Formats

  - Ethernet Frame:
    - Destination address
    - Source address
    - Type
    - Payload

  - ARP Packet:
    - Opcode
      - Request or reply

    - Source MAC address
    - Source IP address
    - Destination MAC address
    - Destination IP address
    - Payload

  - IPv4 Packet:
    - Version
    - TTL
    - Checksum
    - Source IP address
    - Destination IP address
    - Payload

- ACLs refer to TCP ports: ports are like extensions

- IP Header => we do longest match on the destination IP address

  - ACLs also check source IP address
  - Also Protocol field and TTL

- ACL Syntax

  - Different for different vendors
  - Logically, a conjunction of predicates on IP and TCP fields and an action
    - Ex) Dest IP = `129.97.*` and Dest Port = `1433` => drop

  - Most routers allow 100-1,000 of them

- Forwarding Pseudocode

  - ```
    Find input network interfaceL findIfaceByName
    Drop packet if interface is unknown
    
    Read ethernet header and check the eth_type field
    Ignore all but ARP and IPv4 types
    
    If eth_type is ARP:
    	If ARP request packet:
    		Prepare and send ARP response packet
      If ARP response packet
      	Record IP-MAC mapping information in ARP cache
      	Send out all enqueued packets for ARP entry
      	
    If eth_type is IPv4:
    	Verify checksum, length, discard invalid packets
    	Check 5-tuple (IP dest, IP source, protocol, dest, source ports) in input
    	ACL and drop if needed
    
    Use the longest prefix match algorithm to find a next-hop IP address in the routing table
    
    Lookup ARP cache for MAC address mapped to the next hip destination IP address
    	If valid entry found: forward packet
    	Else: queue received packet and send ARP request to discover the IP-MAC
    	mapping
    ```

- Aside on Fragmentation and Reassembly

  - Path MTU instead: modern endnodes find the right size instead of asking the routers to fragment
    - Fields ignored by most routers and in your project





## Lecture 13: Route Computation

- Digression on Fast IP Lookups

  - Approach 1: Uni-bit Trie
    - 32 steps in worst case
    - Considered too slow today
    - Start with the most significant bit at the root and keep walking the trie until you reach a dead ends
  - Approach 2: Multi-bit Trie
    - 11 steps in worst case
    - Slow and too much memory
    - Reduces the height of the trie, but results in duplicate nodes
  - Approach 3: Ternary CAM
    - Memory where each bit can be `0`, `1`, or `*` that can be searched in parallel
    - 1 step in worst case
    - Too much power at high speeds

- Route Computation

  - The Big Picture

    - Only focus on routing within organizations
    - Next lecture is on routing between organizations via BGP

  - Four Parts to Routing

    - Set up addresses and topology: assign IP addresses and connect routers
    - Neighbor determination: endnodes talk to routers (things like ARP), routers to router neighbors
    - Compute routes: most complex piece, this lecture, but only for within organizations
    - Forward packets: as we studied last lectures

  - Flavors of Route Computation

    - Intra-domain routing: routing within an enterprise managed by one entity
      - Often shortest paths
      - Will study two flavors:
        - Distance vector: gossip protocol
          - Has problems with failures, count-to-infinity
        - Link state: more resilient to failures, often used
    - Inter-domain routing: routing between ISPs owned by different entities
      - Policy routing

  - Distance Vector

    - Routers gossip with neighbors to spread information but does badly with node failures
    - Two principal methods for route computation: distance vector (IP) and link state (OSI)
      - We will study both
    - Distance vector: how can we use the spanning tree protocol idea?
      - We found distances to the min ID node by "gossip"
      - Use the same idea for updating distance to all nodes
    - Previously, we kept `(root, distance, parent)`
      - Now, we keep a vector of `(ID, distance)`, hence, distance vector
    - Distance Vector Databases
      - As in spanning tree, we have port and central databases
      - Central is computed based on best port database
        - Use the minimum of all neighbors
        - Send new information to neighbors upon change
    - Link Failures and Distance Vector
      - On link failure, delete stored distance vector for that port
        - Link failure is reported by neighbor discovery (because we haven't received a "hello" from that neighbor for a while)
      - Different from spanning tree in that there is no aging of information except the local aging used to detect link failures
        - Instead, must rely on something called count-to-infinity => when the distance reaches 32
      - Also, unlike spanning tree, you send whenever information changes
        - Periodic sending is a good idea for robustness, but not strictly necessary
      - Data Packet Looping
        - After `A` crashes, `B` and `C` keep thinking the best way to get to `A` is through each other
        - Thus, a data packet destined to `A` will keep looping until either the hop-count in the packet reaches its maximum value or `B` and `C` finally decide that `A` is down

  - Link State

    - Each router broadcasts its local neighborhood to all other routers within its organization, but must solve the bootstrapping problem

    - Link State History

      - The ARPANET is a large national network that is part of the global Internet
        - Classic network in a historic sense
      - Originally, ARPANET used distance vector
        - However, failure recovery times were very slow after node failures because of the count-to-infinity problem
        - Also, data packets kept looping during this period
      - New ARPANET moved to link state routing, which has quicker response to failures and no count-up problem
        - Similar design used by OSPF inside most ISPs

    - Basic Idea

      - Each node knows the default (or manager-settable) cost of its outgoing links
        - Neighbor discovery is used to compile a list of neighbors that are UP
        - This information, along with link costs, is placed in a Link State Packet (LSP)
      - Each source broadcasts its LSP to all other nodes using a primitive flooding mechanism called intelligent flooding
      - After the LSP propagation process stabilizes, each node has a complete and identical picture of the network graph
      - Then, each node `S` uses any shortest path algorithm (i.e., Dijkstra's) to compute the next node on the shortest path from `S` to every other node `D`

    - LSP Generation on Failure

      - If link `AC` fails, neighbor discovery in `A` and `C` will eventually detect failure
      - Only `A` and `C` recompute their LSP values and broadcast their LSPs again to all other nodes
        - Other nodes don't recompute or rebroadcast their LSPs

    - Sequence Numbers

      - LSPs must include sequence numbers to prevent infinite loops during flooding
        - Sequence numbers are associated with source IPs in a table at each router
        - Larger sequence numbers are accepted, equal or smaller are rejected
      - If a sequence number reaches the upper limit, the router can simply reconnect using a different IP
        - Routers have multiple IPs available to them
        - Restart at sequence number 0 and re-flood

    - Dijkstra's Algorithm

      - Start with your own link state packets
      - Once a link is made permanent (found to be the shortest path), you can then look at their LSPs
      - When a new LSP comes in, you must rerun the algorithm

    - Equal Cost Routes

      - Today, especially in data centers, need a lot of parallelism (multiple 10 or 100 Gbps links to get more bandwidth)
      - To use all bandwidth, its very easy to modify Dijkstra's to keep track of all equal cost next hops
      - Because TCP doesn't like reordering within a connection, routers today to ECMP (Equal Cost Multi-Path) by splitting traffic between equal cost next hops based on a hash function that can hash the Dest and Src IP address and Dest/Src TCP ports
      - This hashing idea guarantees no TCP connection is reordered

    - Code

      - ```
        RECEIVE LSP(A, s, D) on PORT P
        	IF s < SEQ(A) THEN:
        		SEND STORED-LSP(A) ON PORT P
        		ACK[A,P] = TRUE
          ELSE IF s > SEQ(A) THEN:
          	IF A = ME THEN: // source must jump
          		SEQ(ME) = s + 1
          		SEND STORED-LSP(A) ON ALL PORTS
          		FOR ALL PORTS Q, ACK[ME, Q] = TRUE
            ELSE:
            	STORED-LSP(A) = LSP(A, s, D)
            	SEND ACK(A, s) ON PORT P
            	SEND STORED-LSP(A) ON ALL PORTS
            	P <> Q FOR ALL PORTS Q <> P, ACK[A, Q] = TRUE
          ELSE:
          	SEQ(ME) = SEQ(ME) + 1
          	SEND ACK(A, s) ON PORT P
          	ACK[A, P] = FALSE
          	
        PERIODICALLY
        	FOR ALL PORTS P and A WITH ACK[A, P] = TRUE DO:
        		SEND STORED-LSP(A) ON PORT P
        		
        RECEIVE ACK(A, s)
        	IF s = SEQ(A) THEN:
        		ACK[A, P] = FALSE
        		
        LINK ON PORT P COMES UP
        	FOR ALL SOURCES A DO:
        		SET ACK[A, P] = TRUE // send all LSPs on P
        ```

  - Looking Back

    - General Principles
      - Best effort: no guarantees (TCP will fix if needed)
      - Soft state: not like the hard state of a database that must be correct; we keep transmitting route updates so if it's wrong, it will fix itself
      - Decentralized: no central person who knows all routes, but things are changing
    - Generalizations
      - Both flavors generalize nicely
      - Can easily generalize distance vector to find minimum bandwidth paths or maximum reliability
      - So does link state
        - Once you have the whole network, it's easy to compute other metrics
        - One famous example is Constrained Shortest Path for traffic engineering and another is equal cost load splitting
    - Conclusions
      - Distance vector is still used as part of a protocol called RIP and Cisco's IGRP
      - Link state or OSPF is used widely within ISPs because it's more reliable after failure and can be easily modified to do traffic engineering based on, say, bandwidth
      - Next lecture, we will see how ISPs use something called policy vectors to compute routes between ISPs instead of merely shortest paths
      - Note how private clouds like Google are doing their own routing based on centralized views so they can give their applications better guarantees



## Lecture 14: Border Gateway Protocol

- Brief Overview
  - Who does policy routing?
    - ISPs
  - Why policy routing?
    - Every ISP is trying to maximize its economic gain amongst competitors
      - i.e., hot potato routing
    - Some entities want to avoid other entities
  - How do we do policy routing?
    - Small modification of distance vector called path vector
- IP Addresses and Prefixes
  - 32 bytes written as `A.B.C.D`, where `A`, `B`, `C`, and `D` are integers from 1 to 255 representing one byte
    - For example, an EE server in CMU can be `128.2.1.155`, where the first byte is `10000000` (remove dots)
  - A prefix is represented by slash or wildcard notation
    - For example, CMU is `128.2/16`, which means that all IP addresses in CMU start with `10000000 00000010 *`
      - `16` is the length of the prefix
  - Another way to encode prefixes is with a mask
    - Represent a `/16` with a bit-mask starting with 16 `1`s followed by 16 `0`s
    - Can AND with mask to find prefix
- Why Inter-domain Routing: Policy
  - Multiple providers implies need for independence and independent policies
  - Different metrics, trust patterns, different charging policies, different administrative and legal requirements (e.g., ARPANET only for government business, Canadian traffic stays within Canada)
  - Not very well developed
    - Basic conflict between abstraction and hierarchies (for scaling) and ability to specify arbitrary policies
- Possible Policies
  - Never use routing domain `X` for any destination
  - Never use domains `X` and `Y`
  - Don't use `X` to get to a destination in domain `Y`
  - Use `X` only as a last resort
  - Minimize number of domains in path
  - Government messages can traverse the ARPANET, but not others
- BGP Overview
  - Border Gateway Protocol (BGP)
    - The canonical path vector protocol
    - How routing gets done on the Internet today
  - BGP Operation
    - Basic BGP and differences from distance vector
    - BGP features (local pref, MED, community)
    - Issues with BGP
  - BGP Alternatives
- Border Gateway Protocol
  - Inter-domain routing protocol for the Internet
    - Prefix-based path-vector protocol
    - Policy-based routing based on AS paths
    - Evolved during the past 28 years
- Basic BGP Operations
  - Border routers cannot to other domains' border routers
  - While connection is alive, exchange route update messages
  - BGP runs over TCP
    - Allows for incremental changes
  - Step-By-Step
    - A node learns multiple paths to the destination
      - Stores all of the routes in a routing table
      - Applies policy to select a single active route, and may advertise the route to its neighbors, depending on its policy
    - Incremental updates, unlike distance vector
      - Announcement
        - Upon selecting a new active route, add own node ID to path and (optionally) advertise to each neighbor
      - Withdrawal
        - If the active route is no longer available, send a withdrawal message to the neighbors
  - A Simple BGP Route
    - Destination prefix
      - e.g., `128.112.0.0/16`
    - Route attributes, including:
      - AS path (e.g., `7018 88`)
      - Next-hop IP address (e.g., `12.127.0.121)`
  - Data packets flow in the opposite direction from BGP updates
    - Notice how next hop info is crucial to build forwarding table at each route used to choose next hop
    - Have to do ARP as well to get MAC address of next hop
  - Distance Vector vs. BGP
    - Only way in distance vector to tune routes is via cost
    - In BGP, one can "control" routes in more complex ways
    - Distance Vector
      - Within an AS
      - Only attribute is cost
      - Always pick and propagate shortest
    - Path Vector
      - Between ASes
      - Multiple attributes
      - Complex
      - Choices settable in config files
- BGP Attributes
  - AS path: the ASes the announcement traversed
  - Next-hop: where the route was heard from
  - Origin: route came from IGP or EGP
  - Local pref: statically configured ranking of routes within AS
  - Multi-exit discriminator: preference for where to *exit* network
  - Community: opaque data used to tag routes that are to be treated equivalently
- BGP Decision Process
  - Default decision for route selection
    - Highest local pref, shortest AS path, lowest MED, prefer eBGP over iBGP, lowest IGP cost, router ID, etc.
  - Many policies built on default decision process, but...
    - Possible to create arbitrary policies in principle
    - Limited only by power of vendor-specific routing language
  - More intricate feature: MEDs
    - Way to do load balancing by passing a hint to next AS
  - Feature 2: Community
    - Way to tag multiple routes with same tag value
    - Then, remote routers can act on tag (e.g., filter)
- BGP Has Lots of Problems
  - Instability
    - Route flapping (network `x.y/z` goes down... tell everyone)
    - Not guaranteed to converge, NP-hard to tell if it does
  - Scalability still a problem
    - Over 1,000,000 network prefixes in default-free table today
    - Tension: want to manage traffic to very specific networks, but also want aggregation
  - Performance
    - Non-optimal, doesn't balance load across paths
- Business Relationships
  - Neighboring ASes have business contracts
    - How much traffic to carry
    - Which destinations to reach
    - How much money to pay
  - Common business relationships
    - Customer-provider
    - Peer-peer
- Multi-Homing
  - Customers may have more than one provider
    - Extra reliability, survive single ISP failure
    - Financial leverage through competition
    - Better performance by selecting better path
    - Gaming the 95th-percentile billing model
- Beyond BGP
  - SND-inspired approaches like Google's Espresso
    - Google border routers talk BGP to the outside world, but send all BGP announcements to a service that also has latency information from Google Apps, and so picks better routers to the external internet
  - Link state versions of BGP (IDRP, Radia proposal)

- Conclusions
  - Link state and distance vector are used to route within a domain/AS/ISP/enterprise
  - BGP is used to compute routes between ASes
  - Basically like distance vector gossip, except you add not just a total cost, but a list of all ASes in path so far
  - AS path helps policy because any router can choose to drop based on ASes in path
  - AS path also helps prevent loops without a hop count
  - BGP has issues and there are alternatives to BGP



## Lecture 15:

- 
