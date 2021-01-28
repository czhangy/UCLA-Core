#!/usr/bin/python

"""

Shuffles input by outputting a random permutation of its input lines, where each output is equally likely

"""

import argparse, string, random, sys

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def getLines(self):
        return self.lines

    def chooseLine(self):
        return random.choice(self.lines)

def main():
    parser = argparse.ArgumentParser(description='Parse through the input file')
    parser.add_argument('filename', nargs='?', type=argparse.FileType('r'), default=sys.stdin)
    parser.add_argument('--echo', '-e', action='store', nargs='*', help='Treat each command line operand as an input line')
    parser.add_argument('--input-range', '-i', action='store', default = '', help='Act as if input came from a file containing the range of unsigned decimal integers lo…hi, one per line.')
    parser.add_argument('--head-count', '-n', action='store', nargs='?', default = 'flagGone', const='failed flag', help="Output at most count lines. By default, all input lines are output.")
    parser.add_argument('--repeat', '-r', action='store_true', help='Repeat output values, that is, select with replacement. With this option the output is not a permutation of the input; instead, each output line is randomly chosen from all the inputs. This option is typically combined with --head-count; if --head-count is not given, shuf repeats indefinitely.')
    args=parser.parse_args(sys.argv[1:]) # cut first element off
    if (args.head_count != 'flagGone'): # if -n flag was present
        try:
            x=int(args.head_count) # check if the input to -n was a valid int
        except:
            parser.error('Input for head count must be a valid integer') # exception thrown if -n input not int
  
    if (args.input_range != ''): # -i flag done
        try:
            numRange=args.input_range.split('-')
            if (int(numRange[1])+1 < int(numRange[0])): # exception if nums are in incorrect order
                parser.error('Invalid input to input range: '+args.input_range)
            numRange=range(int(numRange[0]), int(numRange[1])+1) # get inclusive list
            numRange=list(numRange)
            random.shuffle(numRange)
            for i in numRange:
                print(i)
        except: # exception for non-numeric / non-dash inputs
            parser.error('Invalid input to input range: '+args.input_range)
    elif (args.echo != None): # -e flag done
        try:
            random.shuffle(args.echo) # doesn;t fail on 0 inputs, just exits 
            for i in args.echo:
                print(i)
        except:
            parser.error('Invalid input to echo') # exception catches random failure
    elif (args.repeat): # -r flag done
        if (args.filename.name == '<stdin>'): # stdin
            r = randline(sys.stdin)
        else: # normal execution
            r = randline(args.filename.name)
        if (args.head_count == 'flagGone'): # -n flag not present, infinitely loop
            while (True):
                print(r.chooseLine(), end='')
        else: # -n flag present, perform same checks as below
            if(int(args.head_count) < 0):
               parser.error('Input to head count is an invalid integer: '+args.head_count)
            x = int(args.head_count)
            while (x > 0):
               print(r.chooseLine(), end='')
               x = x-1
    else: # base case done
        try:
            if (args.filename.name == '<stdin>'): # read from stdin
                lines = list((sys.stdin.read()).split('\n'))
                lines = lines[:-1] # get rid of trailing newline
            else: # read in file name
                r = randline(args.filename.name)
                lines = r.getLines()
                for i in range(0, len(lines)): # get rid of all trailing newlines
                    lines[i] = lines[i][:-1]
            random.shuffle(lines) # actual shuffle of lines
            if (args.head_count != 'flagGone'): # if -n flag was present
                if (int(args.head_count) < 0):
                    parser.error('Input to head count is an invalid integer: '+args.head_count)
                lines=lines[:int(args.head_count)] # slice so list fits head count
            for i in lines:
                print(i)
        except: # fails out
            parser.error('Filename invalid')

if __name__ == "__main__":
    main()
