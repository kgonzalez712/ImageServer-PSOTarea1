import React, { Component } from "react";
import { Media, Row, Col, Form, FormGroup, Label, Button, CustomInput, Jumbotron } from 'reactstrap';
import { InitMenu } from '../init-menu/InitMenu';
import './SelectImage.css';
import { Image } from '../../models/image';
import axios from "axios";

export interface IValue {
    value: Image, loading: boolean, image: FormData 
    }
export default class SelectImage extends Component{
  requiresImage: boolean = true;
    

    state = {
      value: Image.Empty,
        image: "",
        imagePath: '',
      };
    
    
    uploadImage (e:any) {
      let img = e.target.files[0]
      let reader = new FileReader();
      reader.readAsDataURL(img);
          reader.onload = function () {
          //me.modelvalue = reader.result;
          console.log(reader.result);
          let b64= reader.result;
          axios.post('http://localhost:1897', b64)
          };
            reader.onerror = function (error) {
            console.log('Error: ', error);
           };
      let fd= new FormData()
    
      fd.append('image', img)
      console.log(img)
      console.log(fd)
    
      
    }


render () {
    return (
        <div>
            <InitMenu/>
            <Jumbotron>
            <Form className="style">
                <Row form>
            <Col md={4}>
              <FormGroup>
                <Media height="230" width="190" id="image" src={this.state.value.url} alt="Generic placeholder image" />
              </FormGroup>
            </Col>
            <Col md={8}>
              <FormGroup>
                <Label>Imagen:</Label>
                  <CustomInput type="file" onChange={this.uploadImage} id="imageUp" name='image' required={this.requiresImage} />
              </FormGroup>
            </Col>
          </Row>
            </Form>

            
            </Jumbotron>
        </div>

        );
    }
  }



