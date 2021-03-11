import React, { Component } from "react";
import './App.css';
import { Route } from 'react-router';
import SelectImage from "./components/select-image/SelectImage";

export default class App extends Component {
  static displayName = App.name;
  render () {
    return (
      <div>
        <Route exact path='/' component={SelectImage} />
      </div>
    );
  }
}
