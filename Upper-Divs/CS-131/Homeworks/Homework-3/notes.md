# Java Shared Memory Performance Races

## Goal

**Perform tests on various synchronization methods in Java, and attempt to design an efficient synchronization system under the JMM**

## `lnxsrv06` Info

- `java -version` output:

  - ```
    openjdk version "15.0.2" 2021-01-19
    OpenJDK Runtime Environment (build 15.0.2+7-27)
    OpenJDK 64-Bit Server VM (build 15.0.2+7-27, mixed mode, sharing)
    ```

- `/proc/meminfo` output:

  - ```
    MemTotal:       65794548 kB
    MemFree:        59944528 kB
    MemAvailable:   63947052 kB
    Buffers:          304048 kB
    Cached:          3674068 kB
    ```

- `/proc/cpuinfo` output:

  - ```
    model name      : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz
    ```

- `/etc/os-release` output:

  - ```
    NAME="Red Hat Enterprise Linux Server"
    VERSION="7.8 (Maipo)"
    ```

- `uname -a` output:

  - ```
    Linux lnxsrv06.seas.ucla.edu 3.10.0-1062.9.1.el7.x86_64 #1 SMP Mon Dec 2 08:31:54 EST 2019 x86_64 GNU/Linux
    ```

## `lnxsrv11` Info

- `java -version` output:

  - ```
    OpenJDK Runtime Environment (build 15.0.2+7-27)
    OpenJDK 64-Bit Server VM (build 15.0.2+7-27, mixed mode, sharing)
    ```

- `/proc/meminfo` output:

  - ```
    MemTotal:       65649184 kB
    MemFree:        59695160 kB
    MemAvailable:   61181228 kB
    Buffers:          141300 kB
    Cached:          1801056 kB
    ```

- `/proc/cpuinfo` output:

  - ```
    model name      : Intel(R) Xeon(R) Silver 4116 CPU @ 2.10GHz
    ```

- `/etc/os-release` output:

  - ```
    NAME="Red Hat Enterprise Linux"
    VERSION="8.2 (Ootpa)"
    ```

- `uname -a` output:

  - ```
    Linux lnxsrv11.seas.ucla.edu 4.18.0-193.19.1.el8_2.x86_64 #1 SMP Wed Aug 26 15:29:02 EDT 2020 x86_64 GNU/Linux
    ```

## `SynchronizedState` Tests

- ### `lnxsrv06`:

    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
              Total time 2.99502 s real, 2.99319 s CPU
              Average swap time 29.9502 ns real, 29.9319 ns CPU
              real    0m3.156s
              user    0m3.145s
              sys     0m0.041s
              ```
            
        - ##### 8 threads:
          
            - ```
                Total time 28.4691 s real, 91.4220 s CPU
                Average swap time 2277.52 ns real, 914.220 ns CPU
                real    0m28.598s
                user    1m23.241s
                sys     0m8.379s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 21.6274 s real, 69.2789 s CPU
                Average swap time 4325.48 ns real, 692.789 ns CPU
                real    0m21.787s
                user    1m3.906s
                sys     0m5.583s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 23.8207 s real, 78.1343 s CPU
                Average swap time 9528.28 ns real, 781.343 ns CPU
                real    0m23.952s
                user    1m11.700s
                sys     0m6.655s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.93878 s real, 2.93692 s CPU
                Average swap time 29.3878 ns real, 29.3692 ns CPU
                real    0m3.089s
                user    0m3.087s
                sys     0m0.041s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 26.8422 s real, 84.8721 s CPU
                Average swap time 2147.37 ns real, 848.721 ns CPU
                real    0m26.987s
                user    1m16.834s
                sys     0m8.249s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 21.2001 s real, 64.7690 s CPU
                Average swap time 4240.01 ns real, 647.690 ns CPU
                real    0m21.322s
                user    0m58.993s
                sys     0m5.985s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 22.2985 s real, 68.7054 s CPU
                Average swap time 8919.38 ns real, 687.054 ns CPU
                real    0m22.444s
                user    1m2.476s
                sys     0m6.453s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 3.11584 s real, 3.11399 s CPU
                Average swap time 31.1584 ns real, 31.1399 ns CPU
                real    0m3.247s
                user    0m3.265s
                
                sys     0m0.039s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 29.1476 s real, 93.5162 s CPU
                Average swap time 2331.81 ns real, 935.162 ns CPU
                real    0m29.270s
                user    1m25.225s
                sys     0m8.521s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 22.9366 s real, 70.1685 s CPU
                Average swap time 4587.32 ns real, 701.685 ns CPU
                real    0m23.135s
                user    1m4.160s
                sys     0m6.232s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 23.4051 s real, 71.8568 s CPU
                Average swap time 9362.03 ns real, 718.568 ns CPU
                real    0m23.534s
                user    1m5.738s
                sys     0m6.342s
                ```

- ### `lnxsrv11`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 3.28289 s real, 3.26886 s CPU
                Average swap time 32.8289 ns real, 32.6886 ns CPU
                real    0m3.395s
                user    0m3.379s
                sys     0m0.029s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 9.80747 s real, 16.2676 s CPU
                Average swap time 784.598 ns real, 162.676 ns CPU
                real    0m9.924s
                user    0m15.994s
                sys     0m0.433s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 11.4357 s real, 19.1080 s CPU
                Average swap time 2287.15 ns real, 191.080 ns CPU
                real    0m11.540s
                user    0m19.077s
                sys     0m0.193s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 11.7409 s real, 19.6070 s CPU
                Average swap time 4696.36 ns real, 196.070 ns CPU
                real    0m11.852s
                user    0m19.587s
                sys     0m0.183s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 3.32105 s real, 3.30623 s CPU
                Average swap time 33.2105 ns real, 33.0623 ns CPU
                real    0m3.456s
                user    0m3.419s
                sys     0m0.027s
                ```
          ```
          
          ```
          
        - ##### 8 threads:
          
            - ```
            Total time 7.27160 s real, 11.0159 s CPU
            Average swap time 581.728 ns real, 110.159 ns CPU
                real    0m7.373s
                user    0m10.658s
                sys     0m0.507s
              ```
            
        - ##### 20 threads:
          
            - ```
                Total time 6.43118 s real, 8.38930 s CPU
                Average swap time 1286.24 ns real, 83.8930 ns CPU
                real    0m6.545s
                user    0m8.373s
                sys     0m0.184s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 8.22381 s real, 12.1588 s CPU
                Average swap time 3289.53 ns real, 121.588 ns CPU
                real    0m8.328s
                user    0m12.162s
                sys     0m0.175s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 3.22266 s real, 3.20846 s CPU
                Average swap time 32.2266 ns real, 32.0846 ns CPU
                real    0m3.323s
                user    0m3.321s
                sys     0m0.030s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 6.39174 s real, 8.92544 s CPU
                Average swap time 511.339 ns real, 89.2544 ns CPU
                real    0m6.499s
                user    0m8.666s
                sys     0m0.407s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 5.65521 s real, 6.58983 s CPU
                Average swap time 1131.04 ns real, 65.8983 ns CPU
                real    0m5.767s
                user    0m6.644s
                sys     0m0.115s
                ```
            
        - ##### 40 threads:
        
            - ```
                Total time 5.58356 s real, 6.49368 s CPU
                Average swap time 2233.43 ns real, 64.9368 ns CPU
                real    0m5.690s
            user    0m6.547s
                sys     0m0.115s
                ```

# `NullState` Tests

- ### `lnxsrv06`:
  
    - ### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.41020 s real, 1.40859 s CPU
                Average swap time 14.1020 ns real, 14.0859 ns CPU
                real    0m1.542s
                user    0m1.572s
                sys     0m0.025s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.254499 s real, 2.00140 s CPU
                Average swap time 20.3599 ns real, 20.0140 ns CPU
                real    0m0.384s
                user    0m2.157s
                sys     0m0.030s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.331819 s real, 4.43479 s CPU
                Average swap time 66.3638 ns real, 44.3479 ns CPU
                real    0m0.466s
                user    0m4.606s
                sys     0m0.048s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 0.440976 s real, 6.46465 s CPU
                Average swap time 176.390 ns real, 64.6465 ns CPU
                real    0m0.567s
                user    0m6.635s
                sys     0m0.066s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.40276 s real, 1.40123 s CPU
                Average swap time 14.0276 ns real, 14.0123 ns CPU
                real    0m1.534s
                user    0m1.555s
                sys     0m0.034s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.269337 s real, 2.04759 s CPU
                Average swap time 21.5470 ns real, 20.4759 ns CPU
                real    0m0.396s
                user    0m2.208s
                sys     0m0.031s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.315291 s real, 4.26412 s CPU
                Average swap time 63.0582 ns real, 42.6412 ns CPU
                real    0m0.440s
                user    0m4.423s
                sys     0m0.053s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 0.359738 s real, 5.20105 s CPU
                Average swap time 143.895 ns real, 52.0105 ns CPU
                real    0m0.510s
                user    0m5.387s
                sys     0m0.059s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.40696 s real, 1.40543 s CPU
                Average swap time 14.0696 ns real, 14.0543 ns CPU
                real    0m1.570s
                user    0m1.549s
                sys     0m0.043s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.261896 s real, 2.02074 s CPU
                Average swap time 20.9517 ns real, 20.2074 ns CPU
                real    0m0.396s
                user    0m2.177s
                sys     0m0.037s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.327947 s real, 4.50026 s CPU
                Average swap time 65.5894 ns real, 45.0026 ns CPU
                real    0m0.478s
                user    0m4.673s
                sys     0m0.047s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 0.434290 s real, 6.26659 s CPU
                Average swap time 173.716 ns real, 62.6659 ns CPU
                real    0m0.568s
                user    0m6.433s
                sys     0m0.072s
                ```
    
- ### `lnxsrv11`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.09217 s real, 1.08568 s CPU
                Average swap time 10.9217 ns real, 10.8568 ns CPU
                real    0m1.197s
                user    0m1.200s
                sys     0m0.025s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.372385 s real, 1.43865 s CPU
                Average swap time 29.7908 ns real, 14.3865 ns CPU
                real    0m0.476s
                user    0m1.542s
                sys     0m0.036s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.372835 s real, 1.33920 s CPU
                Average swap time 74.5671 ns real, 13.3920 ns CPU
                real    0m0.483s
                user    0m1.473s
                sys     0m0.029s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 0.760316 s real, 2.88608 s CPU
                Average swap time 304.127 ns real, 28.8608 ns CPU
                real    0m0.873s
                user    0m3.018s
                sys     0m0.039s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.10918 s real, 1.10373 s CPU
                Average swap time 11.0918 ns real, 11.0373 ns CPU
                real    0m1.210s
                user    0m1.212s
                sys     0m0.033s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.374327 s real, 1.42915 s CPU
                Average swap time 29.9462 ns real, 14.2915 ns CPU
                real    0m0.481s
                user    0m1.539s
                sys     0m0.034s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.375824 s real, 1.38845 s CPU
                Average swap time 75.1648 ns real, 13.8845 ns CPU
                real    0m0.480s
                user    0m1.525s
                sys     0m0.030s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 0.402761 s real, 1.47681 s CPU
                Average swap time 161.104 ns real, 14.7681 ns CPU
                real    0m0.505s
                user    0m1.609s
                sys     0m0.040s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.09360 s real, 1.08736 s CPU
                Average swap time 10.9360 ns real, 10.8736 ns CPU
                real    0m1.195s
                user    0m1.201s
                sys     0m0.026s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 0.340252 s real, 1.30299 s CPU
                Average swap time 27.2201 ns real, 13.0299 ns CPU
                real    0m0.439s
                user    0m1.429s
                sys     0m0.031s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 0.427306 s real, 1.60304 s CPU
                Average swap time 85.4612 ns real, 16.0304 ns CPU
                real    0m0.532s
                user    0m1.737s
                sys     0m0.032s
                ```
            
        - ##### 40 threads:
        
            - ```
                Total time 0.716868 s real, 2.75021 s CPU
                Average swap time 286.747 ns real, 27.5021 ns CPU
                real    0m0.822s
                user    0m2.883s
                sys     0m0.037s
                ```

# `UnsynchronizedState` Tests

- ### `lnxsrv06`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
          - ```
            Total time 1.62308 s real, 1.62154 s CPU
            Average swap time 16.2308 ns real, 16.2154 ns CPU
            real    0m1.756s
            user    0m1.774s
            sys     0m0.038s
            ```
        
        - ##### 8 threads:
          
            - ```
            Total time 4.08690 s real, 32.1630 s CPU
            Average swap time 326.952 ns real, 321.630 ns CPU
            output sum mismatch (-24841 != 0)
                real    0m4.215s
                user    0m32.306s
                sys     0m0.051s
                ```
            
        - ##### 20 threads:
          
          - ```
              Total time 3.04758 s real, 46.3624 s CPU
              Average swap time 609.515 ns real, 463.624 ns CPU
              output sum mismatch (149250 != 0)
              real    0m3.200s
              user    0m46.513s
              sys     0m0.066s
              ```
        
        - ##### 40 threads:
        
          - ```
            Total time 3.15543 s real, 49.5397 s CPU
            Average swap time 1262.17 ns real, 495.397 ns CPU
            output sum mismatch (139639 != 0)
            real    0m3.294s
            user    0m49.684s
            sys     0m0.089s
            ```
    
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.65034 s real, 1.64875 s CPU
                Average swap time 16.5034 ns real, 16.4875 ns CPU
                real    0m1.780s
                user    0m1.796s
                sys     0m0.038s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 5.60614 s real, 44.6881 s CPU
                Average swap time 448.491 ns real, 446.881 ns CPU
                output sum mismatch (-9320 != 0)
                real    0m5.765s
                user    0m44.840s
                sys     0m0.057s
            ```
          
        - ##### 20 threads:
          
            - ```
            Total time 3.70970 s real, 55.7366 s CPU
                Average swap time 741.939 ns real, 557.366 ns CPU
            output sum mismatch (-112161 != 0)
                real    0m3.896s
                user    0m55.870s
                sys     0m0.109s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 3.67548 s real, 57.7968 s CPU
                Average swap time 1470.19 ns real, 577.968 ns CPU
                output sum mismatch (-100929 != 0)
                real    0m3.805s
                user    0m57.979s
                sys     0m0.089s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.67731 s real, 1.67566 s CPU
                Average swap time 16.7731 ns real, 16.7566 ns CPU
                real    0m1.805s
                user    0m1.819s
                sys     0m0.042s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 4.74997 s real, 37.8968 s CPU
                Average swap time 379.997 ns real, 378.968 ns CPU
                output sum mismatch (-19958 != 0)
                real    0m4.882s
                user    0m38.039s
                sys     0m0.063s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 3.35767 s real, 50.3581 s CPU
                Average swap time 671.533 ns real, 503.581 ns CPU
                output sum mismatch (-75882 != 0)
                real    0m3.502s
                user    0m50.521s
                sys     0m0.065s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 3.44104 s real, 53.7098 s CPU
                Average swap time 1376.41 ns real, 537.098 ns CPU
                output sum mismatch (-81947 != 0)
                real    0m3.597s
                user    0m53.883s
                sys     0m0.112s
                ```
    
- ### `lnxsrv11`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.20572 s real, 1.19896 s CPU
                Average swap time 12.0572 ns real, 11.9896 ns CPU
                real    0m1.311s
                user    0m1.305s
                sys     0m0.030s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 2.00253 s real, 7.88475 s CPU
                Average swap time 160.203 ns real, 78.8475 ns CPU
                output sum mismatch (31086 != 0)
                real    0m2.106s
                user    0m8.008s
                sys     0m0.029s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 1.89636 s real, 7.45969 s CPU
                Average swap time 379.272 ns real, 74.5969 ns CPU
                output sum mismatch (28592 != 0)
                real    0m1.999s
                user    0m7.576s
                sys     0m0.040s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 3.88720 s real, 15.3985 s CPU
                Average swap time 1554.88 ns real, 153.985 ns CPU
                output sum mismatch (40749 != 0)
                real    0m3.993s
                user    0m15.522s
                sys     0m0.037s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.21975 s real, 1.21354 s CPU
                Average swap time 12.1975 ns real, 12.1354 ns CPU
                real    0m1.331s
                user    0m1.319s
                sys     0m0.036s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 3.88046 s real, 15.3748 s CPU
                Average swap time 310.436 ns real, 153.748 ns CPU
                output sum mismatch (-8968 != 0)
                real    0m3.983s
                user    0m15.485s
                sys     0m0.040s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 4.34115 s real, 17.2158 s CPU
                Average swap time 868.230 ns real, 172.158 ns CPU
                output sum mismatch (-16398 != 0)
                real    0m4.445s
                user    0m17.336s
                sys     0m0.040s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 3.97569 s real, 15.7162 s CPU
                Average swap time 1590.27 ns real, 157.162 ns CPU
                output sum mismatch (-4944 != 0)
                real    0m4.078s
                user    0m15.860s
                sys     0m0.039s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 1.21276 s real, 1.20504 s CPU
                Average swap time 12.1276 ns real, 12.0504 ns CPU
                real    0m1.314s
                user    0m1.309s
                sys     0m0.038s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 3.45095 s real, 13.6658 s CPU
                Average swap time 276.076 ns real, 136.658 ns CPU
                output sum mismatch (-17184 != 0)
                real    0m3.554s
                user    0m13.784s
                sys     0m0.028s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 3.48352 s real, 13.7460 s CPU
                Average swap time 696.704 ns real, 137.460 ns CPU
                output sum mismatch (-23496 != 0)
                real    0m3.591s
                user    0m13.871s
                sys     0m0.042s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 3.44184 s real, 13.6028 s CPU
                Average swap time 1376.73 ns real, 136.028 ns CPU
                output sum mismatch (-16669 != 0)
                real    0m3.544s
                user    0m13.750s
                sys     0m0.034s
                ```

# `AcmeSafeState` Tests

- ### `lnxsrv06`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.16252 s real, 2.16079 s CPU
                Average swap time 21.6252 ns real, 21.6079 ns CPU
                real    0m2.301s
                user    0m2.319s
                sys     0m0.042s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 15.9321 s real, 126.100 s CPU
                Average swap time 1274.57 ns real, 1261.00 ns CPU
                real    0m16.085s
                user    2m6.264s
                sys     0m0.055s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 9.89013 s real, 154.418 s CPU
                Average swap time 1978.03 ns real, 1544.18 ns CPU
                real    0m10.032s
                user    2m34.601s
                sys     0m0.065s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 9.95894 s real, 157.794 s CPU
                Average swap time 3983.58 ns real, 1577.94 ns CPU
                real    0m10.095s
                user    2m37.977s
                sys     0m0.083s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.17529 s real, 2.17339 s CPU
                Average swap time 21.7529 ns real, 21.7339 ns CPU
                real    0m2.324s
                user    0m2.339s
                sys     0m0.037s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 8.96345 s real, 71.2485 s CPU
                Average swap time 717.076 ns real, 712.485 ns CPU
                real    0m9.094s
                user    1m11.416s
                sys     0m0.058s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 5.69045 s real, 86.6920 s CPU
                Average swap time 1138.09 ns real, 866.920 ns CPU
                real    0m5.833s
                user    1m26.879s
                sys     0m0.066s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 5.84947 s real, 92.9117 s CPU
                Average swap time 2339.79 ns real, 929.117 ns CPU
                real    0m6.002s
                user    1m33.100s
                sys     0m0.074s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.19701 s real, 2.19522 s CPU
                Average swap time 21.9701 ns real, 21.9522 ns CPU
                real    0m2.362s
                user    0m2.359s
                sys     0m0.041s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 6.50802 s real, 51.5850 s CPU
                Average swap time 520.642 ns real, 515.850 ns CPU
                real    0m6.638s
                user    0m51.751s
                sys     0m0.050s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 4.49573 s real, 68.9693 s CPU
                Average swap time 899.146 ns real, 689.693 ns CPU
                real    0m4.628s
                user    1m9.147s
                sys     0m0.074s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 4.38166 s real, 68.5678 s CPU
                Average swap time 1752.66 ns real, 685.678 ns CPU
                real    0m4.539s
                user    1m8.793s
                sys     0m0.064s
                ```
    
- ### `lnxsrv11`:
  
    - #### Size 5 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.58048 s real, 2.56846 s CPU
                Average swap time 25.8048 ns real, 25.6846 ns CPU
                real    0m2.685s
                user    0m2.678s
                sys     0m0.035s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 10.9011 s real, 43.1984 s CPU
                Average swap time 872.088 ns real, 431.984 ns CPU
                real    0m11.003s
                user    0m43.315s
                sys     0m0.035s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 11.6536 s real, 46.2751 s CPU
                Average swap time 2330.72 ns real, 462.751 ns CPU
                real    0m11.761s
                user    0m46.395s
                sys     0m0.045s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 11.6423 s real, 46.2494 s CPU
                Average swap time 4656.91 ns real, 462.494 ns CPU
                real    0m11.746s
                user    0m46.381s
                sys     0m0.037s
                ```
        
    - #### Size 50 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.48382 s real, 2.47083 s CPU
                Average swap time 24.8382 ns real, 24.7083 ns CPU
                real    0m2.589s
                user    0m2.582s
                sys     0m0.042s
                ```
            
        - ##### 8 threads:
          
            - ```
                Total time 9.31282 s real, 36.9742 s CPU
                Average swap time 745.026 ns real, 369.742 ns CPU
                real    0m9.415s
                user    0m37.096s
                sys     0m0.035s
                ```
            
        - ##### 20 threads:
          
            - ```
                Total time 9.27939 s real, 36.8407 s CPU
                Average swap time 1855.88 ns real, 368.407 ns CPU
                real    0m9.386s
                user    0m36.972s
                sys     0m0.037s
                ```
            
        - ##### 40 threads:
          
            - ```
                Total time 8.92297 s real, 35.4057 s CPU
                Average swap time 3569.19 ns real, 354.057 ns CPU
                real    0m9.028s
                user    0m35.551s
                sys     0m0.041s
                ```
        
    - #### Size 100 array:
      
        - ##### 1 thread:
          
            - ```
                Total time 2.50308 s real, 2.47748 s CPU
                Average swap time 25.0308 ns real, 24.7748 ns CPU
                real    0m2.609s
                user    0m2.600s
                sys     0m0.029s
                ```
            
        - ##### 8 threads:
          
            - ```
            Total time 7.23213 s real, 26.2210 s CPU
                Average swap time 578.570 ns real, 262.210 ns CPU
                real    0m7.340s
                user    0m26.348s
                sys     0m0.033s
                ```
            
        - ##### 20 threads:
        
          - ```
            Total time 7.76318 s real, 30.8306 s CPU
            Average swap time 1552.64 ns real, 308.306 ns CPU
            real    0m7.867s
            user    0m30.960s
            sys     0m0.039s
            ```
        
        - ##### 40 threads:
        
            - ```
                Total time 7.34787 s real, 29.1347 s CPU
            Average swap time 2939.15 ns real, 291.347 ns CPU
                real    0m7.461s
                user    0m29.287s
                sys     0m0.049s
                ```

