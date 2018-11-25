import java.io.*;
import java.util.*;


public class B {
    public static void main(String[] args) throws IOException {
        //BufferedReader br1 = new BufferedReader(new InputStreamReader(System.in));
        //PrintWriter out = new PrintWriter(new File("output.txt"));
        Scanner in = new Scanner (new File("brackets.in"));
        PrintWriter out = new PrintWriter(new File("brackets.out"));
        String skob = in.next();
        StringBuilder stc = new StringBuilder(); 
        boolean flag = true;
        for (int i = 0; i < skob.length(); i++) {
            if (stc.length() == 0) {
                stc.append(skob.charAt(i));
            } else {
                if ((stc.charAt(stc.length() - 1) == '[' && (char)skob.charAt(i) == ']') ||(stc.charAt(stc.length() - 1) == '(' && (char)skob.charAt(i) == ')') || (stc.charAt(stc.length() - 1) == '{' && (char)skob.charAt(i) == '}')) {
                    stc.deleteCharAt(stc.length() - 1);
                } else {
                    stc.append(skob.charAt(i));
                }
            }
        }
        if (stc.length() != 0) {
            flag = false;
        }
        if (flag) {
            out.print("YES");
        } else {
            out.print("NO");
        }
        out.close();     
    }
}