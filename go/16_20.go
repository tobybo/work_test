
package main;

import (
    "fmt";
    "os";
    "bufio";
);

func main() {
    var phone_map [26]byte = [26]byte{2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
    var num string;
    fmt.Scan(&num);
    var s string;
    var inputReader = bufio.NewReader(os.Stdin);
    s, _ = inputReader.ReadString('\n');
    var input []string = explode(s, ',');
    //fmt.Println("s: ", s, " len: ", len(input));
    var ans []string;
    for _, s := range input {
        for i, c := range s {
            //fmt.Println("c: ",c,", c-a: ",c - 'a');
            if phone_map[c - 'a'] != num[i] - '0' {
                break;
            }
            if i == len(s) - 1 {
                ans = append(ans, s);
                // fmt.Println("-----------");
                fmt.Println(s);
                // fmt.Println("-----------");
            }
        }
    }
}

func explode(s string, n rune) []string {
    var v []string = make([]string, 0, len(s));
    var buff string = "";
    for _, c := range s {
        if c != ' ' && c != '"' && c != n && c != '\n' {
            buff += string(c);
        }
        if c == n && buff != "" {
            v = append(v, buff);
            //fmt.Println("buff: ", buff);
            buff = "";
        }
    }
    if buff != "" {
        v = append(v, buff);
        //fmt.Println("buff: ", buff);
    }
    return v
}
