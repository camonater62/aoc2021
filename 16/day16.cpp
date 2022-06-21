#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

int process_packet(string& packet, int * version_count, long * value) {
    int bits_processed = 0;

   // cout << packet << endl;
    // first three bits are version
    int version = stoi(packet.substr(0, 3), NULL, 2);
    packet = packet.substr(3);
    bits_processed += 3;
    *version_count += version;

    // next three bits are type id
    int type = stoi(packet.substr(0, 3), NULL, 2);
    packet = packet.substr(3);
    bits_processed += 3;

    // cout << "Type:" << type << endl;

    if (type == 4) {
    // for a type 4 id:
    //      read five bits at a time until the first bit is 0
        bool valid = true;
        string bits;
        while (valid) {
            string sub_bits = packet.substr(0, 5);
            packet = packet.substr(5);
            bits_processed += 5;

       //     cout << sub_bits << endl;

            valid = (sub_bits[0] == '1');
            bits += sub_bits.substr(1);
        }

       // cout << bits << endl;
        *value = stol(bits, NULL, 2);
        // cout << stoi(bits, NULL, 2) << endl;
    } else {
    // any other id:
    //      read one bit,
        int mode = stoi(packet.substr(0, 1), NULL, 2);
        packet = packet.substr(1);
        bits_processed += 1;

        vector<long> values;
    //    cout << "Mode:" << mode << endl;
        if (mode == 0) {
    //      if 0, next 15 bits are total bit length of sub packets
            int bit_length = stoi(packet.substr(0, 15), NULL, 2);
            packet = packet.substr(15);
            bits_processed += 15;
       //     cout << bit_length << endl;

            int sub_processed = 0;
            while (sub_processed < bit_length) {
                long val = 0;
                sub_processed += process_packet(packet, version_count, &val);
                values.push_back(val);
            //    cout << "SP: " << sub_processed  << "/" << bit_length << endl;
            }
            bits_processed += sub_processed;
        } else if (mode == 1) {
    //      if 1, next 11 is the number of sub packets
            int num_packets = stoi(packet.substr(0, 11), NULL, 2);
            packet = packet.substr(11);
            bits_processed += 11;

          //  cout << num_packets << endl;
            int sub_processed = 0;
            for (int i = 0; i < num_packets; i++) {
                long val = 0;
                sub_processed += process_packet(packet, version_count, &val);
                values.push_back(val);
            }
            bits_processed += sub_processed;
        }

        switch (type) {
            case 0:
                // SUM
                *value = 0;
                for (long i : values) {
                    *value += i;
                }
                break;
            case 1:
                // PRODUCT
                *value = 1;
                for (long i : values) {
                    *value *= i;
                }
                break;
            case 2:
                // MINIMUM
                *value = values[0];
                for (long i : values) {
                    *value = min(i, *value);
                }
                break;
            case 3:
                // MAXIMUM
                *value = values[0];
                for (long i : values) {
                    *value = max(i, *value);
                }
                break;
            // BELOW ALWAYS HAVE 2 SUB-PACKETS
            case 5:
                // GREATER THAN
                if (values[0] > values[1]) {
                    *value = 1;
                } else {
                    *value = 0;
                }
                break;
            case 6:
                // LESS THAN
                if (values[0] < values[1]) {
                    *value = 1;
                } else {
                    *value = 0;
                }
                break;
            case 7:
                // EQUAL
                if (values[0] == values[1]) {
                    *value = 1;
                } else {
                    *value = 0;
                }
                break;
        }
    }

    return bits_processed;
}

int main() {
    string rawhex;
    getline(cin, rawhex);

    string binary;
    for (int i = 0; i < rawhex.length(); i++) {
        binary += bitset<4>(stoi(rawhex.substr(i, 1), nullptr, 16)).to_string();
    }

    int p1count = 0;
    long p2count = 0;
    process_packet(binary, &p1count, &p2count);

    cout << "P1: " << p1count << endl;
    cout << "P2: " << p2count << endl;

    return 0;
}
