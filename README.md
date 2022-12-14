<h1 align="center" style="font-weight: bold">
        strcon
</h1>       

<p align="center">
    <img src="https://img.shields.io/badge/os-linux-red">
    <img src="https://img.shields.io/badge/os-mac-red"></a>
    <img src="https://img.shields.io/badge/os-windows-red"></a>
    </br>
</p>

---
<h4 align="center">
A tool written in C to convert base numbers to human readable string and vice versa.
</h4>

---

<h2>
Usage
</h2>

### Compile
> make
---

### Help

>strcon -h

Output:

```nani

Usage: strcon <type|conversion> <input> [ data | file ] -o outfile.txt

|CLI options|:-
   type/conversion:
      -O  converts octal dump to string.
      -B  converts binary dump to string.
      -D  converts decimal dump to string.
      -X  converts hexadecimal dump to string.
          [if -s flag is specified, it converts string to <type>.]

   input:
      -i  takes next argument as data string.
      -f  takes next argument as filename.

   optional:
      -o  takes next argument as filename.
          (if filename is not given, default is strcon_out.)


```
---
### __Binary to String__

```bash
strcon -B -f exfiles/bin.txt
```

Output:

<pre>
Follow us at <a target="_blank" href="https://instagram.com/flag_predators">https://instagram.com/flag_predators</a>
</pre>

### __String to Binary__

```bash
strcon -s -B -i "CTFS :)"
```

Output:

<pre>
01000011 01010100 01000110 01010011 00100000 00111010 00101001
</pre>

---
### __Octal to String__

```bash
strcon -O -i "110 141 143 153 145 162 40 155 157 155 145 156 164 40 72 76"
```

Output:

<pre>
Hacker moment :>
</pre>

### __String to Octal__

```bash
strcon -s -O -f exfiles/oct_out
```

Output:

<pre>
110 141 143 153 40 124 145 150 40 127 157 162 154 144 41
</pre>

---
### __Hexadecimal to String__

```bash
strcon -X -i "53 74 61 72 20 74 68 69 73 20 70 72 6f 6a 65 63 74 20 3a 29"
```

Output:

<pre>
Star this project :)
</pre>

### __String to Hexadecimal__

```bash
strcon -s -X -f exfiles/WIT
```

Output:

<pre>
0x57 0x68 0x61 0x74 0x65 0x76 0x65 0x72 0x20 0x69 0x74 0x20 0x74 0x61 0x6b 0x65 0x73 0x2e 0x2e 0x2e 
</pre>

---
### __Decimal to String__

```bash
strcon -D -i "72 97 118 101 32 97 32 110 105 99 101 32 100 97 121 32 40 59"
```

Output:

<pre>
Have a nice day (;
</pre>

### __String to Decimal__

```bash
strcon -D -f exfiles/decimal -s
```

Output:

<pre>
76 101 116 115 32 103 114 105 110 100 32 40 59
</pre>

---
---

### **Redirecting output to a file:**
---

##### Using the redirection operator↴

```bash
strcon -X -i "0x68 0x65 0x78 0x61 0x64 0x65 0x63 0x69 0x6d 0x61 0x6c" > exfiles/hex_out.txt
```

##### Using the -o argument with a filename↴

```bash
strcon -O -i "143 157 156 164 162 151 142 165 164 145 40 72 51" -o exfiles/oct_out
```

##### Using the -o argument without a filename↴

```bash
strcon -D -i "105 100 107 32 105 100 99 46" -o
```
>ps: "-o" without a parameter uses the default filename 'strcon_out'
