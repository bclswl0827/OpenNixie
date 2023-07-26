const isFeatureSupport = (feature: string) => {
    if (feature in navigator) {
        return true;
    }

    return false;
};

export default isFeatureSupport;
