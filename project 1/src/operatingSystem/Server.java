package operatingSystem;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread {
    public static final int PORT_NUMBER = 8081;

    protected Socket socket;

    private Server(Socket socket) {
        this.socket = socket;
        System.out.println("New client connected from " + socket.getInetAddress().getHostAddress());
        start();
    }

    public void run() {
        InputStream in = null;
        OutputStream out = null;
        try {
            in = socket.getInputStream();
            out = socket.getOutputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            String request;
            
            while ((request = br.readLine()) != null) {
                System.out.println("server-data: " + request);
            	 char [] covert=request.toCharArray();
            	 char c = covert[0];
                 int i = 0;
                 if("q".equals(request)) {
                	 System.exit(0);
                	 break;
                 }
                 while(c!='\0'){
                   if(c>=65&&c<=90){ //A-Z
                	   covert[i]=(char) (covert[i]-3);             
                	   if(covert[i]>90)
                		   covert[i]= (char) ((covert[i]%90)+65);
                   }
                   if(covert[i]<65)
                	   covert[i]=(char)(covert[i]+26);
                   if(c>=97&&c<=122){
                	   covert[i]=(char) (covert[i]-3);
                       if(covert[i]>122)
                    	   covert[i]= (char) ((covert[i]%122)+97);
                   }
                   if(covert[i]<97 && covert[i]>=91) //a-z
                	   covert[i]=(char)(covert[i]+26); //out of a-z,we are adding 26(number of the a-z group) to return the a-z
                   if(c==32)
                	   covert[i]=c;
                   i++;
                   if(i<covert.length)
                      c=covert[i];
                   else break;
                 }
                 request=String.valueOf(covert);
                 System.out.println("server-decrypted data: " + request);
                 request += '\n';
                 out.write(request.getBytes());
            }

        } catch (IOException ex) {
            System.out.println("Unable to get streams from client");
        } finally {
            try {
                in.close();
                out.close();
                socket.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("SocketServer Example");
        ServerSocket server = null;
        try {
            server = new ServerSocket(PORT_NUMBER);
            while (true) {
                new Server(server.accept());
            }
        } catch (IOException ex) {
            System.out.println("Unable to start server.");
        } finally {
            try {
                if (server != null)
                    server.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}