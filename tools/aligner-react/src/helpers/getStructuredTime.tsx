export interface StructuredTime {
    year: number;
    month: number;
    day: number;
    week: number;
    hour: number;
    minute: number;
    second: number;
}

const getStructuredTime = (): StructuredTime => {
    const date = new Date();

    return {
        year: date.getFullYear(),
        month: date.getMonth(),
        day: date.getDate(),
        week: date.getDay(),
        hour: date.getHours(),
        minute: date.getMinutes(),
        second: date.getSeconds(),
    };
};

export default getStructuredTime;
