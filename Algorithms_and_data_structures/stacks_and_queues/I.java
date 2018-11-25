import java.io.*;
import java.util.*;
import java.lang.Math;


public class I {
    public static void main(String[] args) throws IOException {
        int[] stack = new int[500020];
        int[] stack_min = new int[500020];
        BufferedReader br = new BufferedReader(new FileReader("hemoglobin.in"));
        PrintWriter out = new PrintWriter(new File("hemoglobin.out"));
        //BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
        String tmp = br.readLine(); 
        StringBuilder str = new StringBuilder();
        while (tmp != null) {
            str.append(tmp);
            str.append(' ');
            tmp = br.readLine();
        }
        //System.out.println(str.toString());
        StringTokenizer in = new StringTokenizer(str.toString());
        int n = Integer.parseInt(in.nextToken());
        int k1 = 0;
        int k2 = 0;
        for (int i = 0; i < n; i++) {
            String type = in.nextToken();
            if (type.charAt(0) == '+') {
                stack[k1++] = Integer.parseInt(type);
                if (k2 == 0) {
                    stack_min[k2] = stack[k1 - 1];
                } else {
                    stack_min[k2] = stack[k1 - 1] + stack_min[k2 - 1];
                }
                k2++;
                continue;
            }
            if (type.charAt(0) == '-') {
                k1--;
                k2--;
                out.println(stack[k2]);
                continue;
            }
            if (type.charAt(0) == '?') {
                String k = type.substring(1, type.length());
                if (k2 - 1 - Integer.parseInt(k) != -1) {
                    out.println(stack_min[k2 - 1] - stack_min[k2 - 1 - Integer.parseInt(k)]);
                } else {
                    out.println(stack_min[k2 - 1]);
                }
            }
        }        
        out.close();     
    }
}