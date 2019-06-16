        lw      0       1       input   load reg1 with 20 (symbolic address)
        add     1       1       2       save reg2 with input * 2 data hazard needs forwarding
        add     2       2       3       save reg3 with input * 4 data hazard needs forwarding
        add     3       3       4       save reg4 with input * 8 data hazard needs forwarding
        add     2       4       5       save reg5 with input * (8 + 2) data hazard needs forwarding
        noop
        halt
input   .fill   20
pos1    .fill   1
mempos  .fill   100
