#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define FRAME_SIZE 10
void uart_transmit(uint8_t data,uint8_t frame[FRAME_SIZE]){
    frame[0]=0;
    for(int i=0;i<8;i++){
        frame[i+1]=(data>>i) & 1u;
    }
    frame[9]=1;
}
bool uart_receive(const uint8_t frame[FRAME_SIZE],uint8_t*received){
    if(frame[0]!=0 || frame[9]!=1){
        printf("Error: Invalid frame format\n");
        return false;
    }
    uint8_t value=0;
    for(int i=0;i<8;i++){
        printf("%u ",(unsigned int)frame[i+1] );
        value|=(uint8_t)((frame[i+1] & 1u)<<i);
    }
    
    *received=value;
    return true;
}
int main(){
    char input[100];
    uint8_t frame[FRAME_SIZE];
    printf("Enter a message to transmit (max 100 characters): ");
    
    if(fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    for(int i=0;input[i]!='\0' && input[i]!='\n';i++){
        uart_transmit(input[i], frame);
        printf("Transmitting character: %c\n", input[i]);
        uint8_t received_char = 0;
        if(uart_receive(frame, &received_char)){    
            printf("Received ASCI character: %u\n", (unsigned int) received_char);
            printf("Received character: %c\n",(char) received_char);
        } else {
            printf("Failed to receive character.\n");
        }

    }
    return 0;
    
}