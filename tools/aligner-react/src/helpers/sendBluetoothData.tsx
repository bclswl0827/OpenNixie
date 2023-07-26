const sendBluetoothData = async (
    characteristic: BluetoothRemoteGATTCharacteristic | undefined,
    data: number[]
): Promise<void> => {
    const delay = (ms: number) =>
        new Promise((resolve) => setTimeout(resolve, ms));

    for (let i of data) {
        await characteristic?.writeValue(new Uint8Array([i]));
        await delay(10);
    }

    await delay(10);
};

export default sendBluetoothData;
