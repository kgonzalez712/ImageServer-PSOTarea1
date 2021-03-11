import logo from '../assets/img/imagen.png';

export class Image{
    constructor(
        public id?: string,
        public url: string = logo
    ){ }
    
    public static get Empty(): Image{return new Image()}
}