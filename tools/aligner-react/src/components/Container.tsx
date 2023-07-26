import { Component, ReactNode } from "react";
import CONFIG from "../config";

export interface ContainerProps {
    children: ReactNode | ReactNode[];
}

export default class Container extends Component<ContainerProps> {
    componentDidMount(): void {
        const { title } = CONFIG.global_settings;
        document.title = title;
    }
    render() {
        const { children } = this.props;
        const childrenArr = Array.isArray(children) ? children : [children];

        return (
            <div className="p-4 min-h-screen grid place-content-center bg-gray-700 text-white">
                <main className="container flex flex-col lg:flex-row gap-8 lg:gap-10">
                    {childrenArr.map((item, index) => (
                        <div key={index}>{item}</div>
                    ))}
                </main>
            </div>
        );
    }
}
