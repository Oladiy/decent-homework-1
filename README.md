## **Project description**

A program that evenly and deterministically distributes exam tickets among students by name.

Required options:

[--file | -f] - path to file with names,

[--numtickets | -n] - amount of tickets ∈ [0; 4294967295],

[--parameter | -p] - distribution-changing parameter ∈ [0; 4294967295].


## **Build**

`g++ distribute_tickets.cpp -o distribute_tickets`

## **Run**
`./distribute_tickets --file <path to file> --numtickets <positive integer> --parameter <positive integer>`

or 

`./distribute_tickets -f <path to file> -n <positive integer> -p <positive integer>`

**Example**

`./distribute_tickets --file students.txt --numtickets 20 --parameter 452`
