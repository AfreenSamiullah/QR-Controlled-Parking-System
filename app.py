# Python QR Generator (parking_control.py)
import qrcode
import cv2
import time
from gpiozero import DigitalInputDevice

ir_sensor = DigitalInputDevice(4)  # GPIO4 for IR sensor
current_slot = ["A1", "A2", "B1", "B2"]
slot_index = 0

def generate_qr(slot_id):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    qr.add_data(slot_id)
    qr.make(fit=True)
    img = qr.make_image(fill_color="black", back_color="white")
    img.save(f"{slot_id}.png")
    return slot_id

while True:
    if ir_sensor.value == 0:  # Object detected
        if slot_index < 4:
            assigned_slot = generate_qr(current_slot[slot_index])
            print(f"Assigned Slot: {assigned_slot}")
            
            # Display QR code
            img = cv2.imread(f"{assigned_slot}.png")
            cv2.imshow("Parking QR", img)
            cv2.waitKey(3000)
            cv2.destroyAllWindows()
            
            slot_index += 1
        else:
            print("Parking Full!")
    time.sleep(0.1)
