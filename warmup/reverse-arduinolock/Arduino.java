import java.util.*;

class Arduino {
    public static void main(String args[]) {
        Arduino door = new Arduino();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter vault password: ");
        
        String input = scanner.next();

        if (door.check(input)) {
            System.out.println("Access granted.");            
        } else {
            System.out.println("Access denied!");
        }
    }


    public boolean check(String password) {
        if (password.length() != 32) {
            return false;
        }
        char[] buffer = new char[32];
        int i;
        for (i=0; i<8; i++) {
            buffer[i] = password.charAt(i);
        }
        for (; i<16; i++) {
            buffer[i] = password.charAt(23-i);
        }
        for (; i<32; i+=2) {
            buffer[i] = password.charAt(46-i);
        }
        for (i=31; i>=17; i-=2) {
            buffer[i] = password.charAt(i);
        }
        String s = new String(buffer);
        return s.equals("jU5t_a_sna_3lpm1dg347_u_4_mfr54b");
    }
}