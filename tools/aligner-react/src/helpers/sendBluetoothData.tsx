const sendBluetoothData = async (
    characteristic: BluetoothRemoteGATTCharacteristic | undefined,
    data: number[]
): Promise<void> => {
    const delay = (ms: number) =>
        new Promise((resolve) => setTimeout(resolve, ms));

    for (let i of data) {
        await characteristic?.writeValueWithoutResponse(new Uint8Array([i]));
        await delay(50);
    }

    await delay(100);
};

export default sendBluetoothData;
