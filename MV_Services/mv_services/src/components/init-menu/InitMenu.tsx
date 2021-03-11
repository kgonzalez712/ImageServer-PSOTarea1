import React, { Component, useState } from 'react';
import { Nav, Collapse, Container, Navbar, NavbarBrand, NavbarToggler, NavItem, NavLink } from 'reactstrap';
import { Link } from 'react-router-dom';
import './InitMenu.css';
import logo from '../../assets/img/Logo-MV-services.png'

export class InitMenu extends Component {
    static displayName = InitMenu.name;
    state: any;

    constructor (props: any) {
        super(props);

        this.toggleInitbar = this.toggleInitbar.bind(this);
        this.state = {
          collapsed: true
        };
      }
    
      toggleInitbar () {
        this.setState({
          collapsed: !this.state.collapsed
        });
      }

      

      render () {
        return (
          <header>
            <Navbar className="navbar-expand-sm navbar-toggleable-sm ng-white border-bottom box-shadow navfondo mb-3" light>
            <div className="abs-center">
              <Container>
                <NavbarBrand tag={Link} to="/">
                    <img src={logo} alt="logo"/>
                    </NavbarBrand>
                <NavbarToggler onClick={this.toggleInitbar} className="mr-2" />
              </Container>
              </div>
            </Navbar>
          </header>
        );
      }
    
}