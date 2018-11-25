import java.io.*;
import java.util.*;


public class C {
    public static void main(String[] args) throws IOException {
        Stack<Integer> st = new Stack<Integer>();
        Scanner in = new Scanner(new File("postfix.in"));
        PrintWriter out = new PrintWriter(new File("postfix.out"));
        //BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String tmp; 
        while (in.hasNext()){
            tmp =in.next();
            if (tmp.equals("-") ||tmp.equals("*") ||tmp.equals("+")) {
                if (tmp.equals("-")) {
                    int value = st.pop();
                    value = st.pop() - value;
                    st.push(value); 
                } else {
                    if (tmp.equals("+")) {
                        st.push(st.pop() + st.pop()); 
                    } else {
                        st.push(st.pop() * st.pop());
                    }
                }             
            } else {
                st.push(Integer.parseInt(tmp));
            }
        }
        
        out.println(st.pop());
        out.close();     
    }
}