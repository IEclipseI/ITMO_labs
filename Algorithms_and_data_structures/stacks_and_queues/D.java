import java.io.*;
import java.util.*;
import java.lang.Math;


public class D {
    public static void main(String[] args) throws IOException {
        int[] stack = new int[1000000];
        int[] stack_min = new int[1000000];
        BufferedReader br = new BufferedReader(new FileReader("stack-min.in"));
        PrintWriter out = new PrintWriter(new File("stack-min.out"));
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
            int type = Integer.parseInt(in.nextToken());
            if (type == 1) {
                stack[k1++] = Integer.parseInt(in.nextToken());
                if (k2 == 0) {
                    stack_min[k2] = stack[k1 - 1];
                } else {
                    stack_min[k2] = Math.min(stack[k1 - 1], stack_min[k2 - 1]);
                }
                k2++;
                continue;
            }
            if (type == 2) {
                k1--;
                k2--;
                continue;
            }
            if (type == 3) {
                out.println(stack_min[k2 - 1]);
            }
        }        
        out.close();     
    }
}