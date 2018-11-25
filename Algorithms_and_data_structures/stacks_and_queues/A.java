import java.io.*;
import java.util.*;


public class A {
    public static void main(String[] args) throws IOException {
        Stack<Integer> st = new Stack<Integer>();
        BufferedReader br1 = new BufferedReader(new FileReader("decode.in"));
        PrintWriter out = new PrintWriter(new File("decode.out"));
        //BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int ch = br1.read();
        int stcSize = 0;
        while (ch != -1) {
            if (stcSize != 0) {
                if (st.peek() == ch) {
                    st.pop();
                    stcSize--;
                } else {
                    st.push(ch);
                    stcSize++;
                } 
            } else {
                st.push(ch);
                stcSize++;
            }
            ch = br1.read();
        }
        StringBuilder sb = new StringBuilder();
        Stack<Integer> st1 = new Stack<Integer>();
        for (int i = 0; i < stcSize; i++) {
            st1.push(st.pop());
        }
        for (int i = 0; i < stcSize; i++) {
            sb.append((char)(st1.pop() - 0));
        }
        out.println(sb.toString());
        out.close();     
    }
}