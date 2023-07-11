
package main;

import (
        "fmt";
        conv "strconv";
        "os";
        "bufio";
);

func main() {
    var s string;
    var inputReader = bufio.NewReader(os.Stdin);
    s, _ = inputReader.ReadString('\n');
    var input []int = explode(s, ',');
    wiggleSort(input);
    for _, val := range input {
        fmt.Print(val, " ");
    }
    fmt.Println();
}

func explode(s string, n rune) []int {
    var v []int = make([]int, 0, len(s));
    var buff string = "";
    for _, c := range s {
        if c != ' ' && c != '"' && c != n && c != '\n' {
            buff += string(c);
        }
        if c == n && buff != "" {
            val, _ := conv.Atoi(buff);
            v = append(v, val);
            //fmt.Println("buff: ", buff);
            buff = "";
        }
    }
    if buff != "" {
        val, _ := conv.Atoi(buff);
        v = append(v, val);
        //fmt.Println("buff: ", buff);
    }
    return v
}


func wiggleSort(nums []int)  {
    var high bool = false;
    for i := 1; i < len(nums); i++ {
        if (high && nums[i] < nums[i - 1]) || (!high && nums[i] > nums[i - 1]) {
            swap(&nums[i], &nums[i - 1]);
        }
        high = !high;
    }
}

func swap(a *int, b *int) {
    *a, *b = *b, *a;
}

